#include "combattracker.h"
#include <QDebug>

CombatTracker::CombatTracker(QObject *parent) : QObject(parent)
{
    battleStarted = false;
    myCurrentTick = 0;
}

CombatTracker::~CombatTracker()
{
    qDeleteAll(myTargets);
}

void CombatTracker::addCombatant(Combatant *add)
{
    add->setParent(this);
    add->joinBattle();

    QMultiMap<int, Combatant * > *hostMap;
    if(!battleStarted)
    {
        hostMap = &currentRoundMap;
    }
    else
    {
        hostMap = &nextRoundMap;
    }


    hostMap->insertMulti(add->initiative(),add);

    myTargets.append(add);
    emit targetsChanged();
    add->setList(&myTargets);
    connect(this, SIGNAL(targetsChanged()),add,SIGNAL(targetsChanged()));

    if(!battleStarted){
        if(myCurrentTick < add->initiative())
            myCurrentTick = add->initiative();
        emit currentTicksChanged();
        emit currentRoundChanged();
    }
    else
    {
        emit  nextTicksChanged();
        emit nextRoundChanged();
    }
}
void CombatTracker::attack(int attackerIndex, int attackingWeapon, int defenderIndex, int defendingWeapon, int attackType, int defenseType)
{
    Combatant *attacker = myCurrentRound[attackerIndex];
    Combatant *defender = myTargets[defenderIndex];

    QList<Combatant *> *host = myCurrentRound.contains(defender)? &myCurrentRound : &myNextRound;

    Weapon *aWeapon = attacker->weapon(attackingWeapon);
    Weapon *dWeapon = defender->weapon(defendingWeapon);
    int attackResult = D10::roll(std::max(attacker->attack((CombatConstants::Attack)attackType, aWeapon),0)) - defender->defense((CombatConstants::Defense)defenseType, dWeapon);
    if(attackResult > 0)
    {
        int damagePool = attacker->damage((CombatConstants::Attack)attackType, aWeapon) + ((CombatConstants::Attack)attackType == CombatConstants::Withering)? attackResult : 0;
        int damageResult = defender->takeDamage((CombatConstants::Attack)attackType,damagePool,aWeapon->overwhelming(),aWeapon->woundType());
        if((CombatConstants::Attack)attackType == CombatConstants::Withering)
        {
            attacker->changeInitiative(1+damageResult);
        }
        else
            attacker->resetInitiative();
    }
    else
    {
        if((CombatConstants::Attack)attackType == CombatConstants::Decisive)
        {
            int iniTemp = attacker->initiative();
            if(attacker->initiative() < 11)
                attacker->changeInitiative(-2);
            else
                attacker->changeInitiative(-3);
            if(iniTemp > 0 && attacker->initiative() < 1)
            {
                attacker->changeInitiative(-5);
            }
        }
    }


    binaryInsertion(&myNextRound,attacker, 0,myNextRound.count());
    myCurrentRound.removeAt(attackerIndex);


    host->removeOne(defender);

    if(!(defender->isDead()||defender->isIncapacitated()))
        binaryInsertion(host, defender,0, host->count());


    if(myCurrentRound.count() < 1)
    {
        myCurrentRound.swap(myNextRound);
    }
    myCurrentRound.first()->refreshTurn();
    emit currentRoundChanged();
    emit nextRoundChanged();
}

void CombatTracker::modifyCombatant(Combatant* subject, int unit, int amount, bool done)
{
    QMultiMap<int, Combatant * > *hostMap = currentRoundMap.contains(subject->initiative(),subject)? &currentRoundMap : &nextRoundMap;
    int tick = subject->initiative();
    if(amount != 0)
    {

        if(unit == 0)
            subject->changeInitiative(amount);
        else
            subject->suffer(std::abs(amount),(CombatConstants::Wounds)unit);
    }

    hostMap->remove(tick,subject);
    if(done)
    {
        hostMap =  &nextRoundMap;
    }


    if(!(subject->isDead()||subject->isIncapacitated()))
        hostMap->insertMulti(subject->initiative(), subject);
    else
        myTargets.removeOne(subject);

    if(currentRoundMap.values(myCurrentTick).count() < 1)
    {
        myCurrentRound.clear();
        if(currentRoundMap.count() < 1)
        {
            currentRoundMap.swap(nextRoundMap);
            myNextRound.clear();
        }
        myCurrentTick = currentTicks()[0].toInt();
        foreach(Combatant* combat,currentRoundMap.values(myCurrentTick))
        {
            combat->refreshTurn();
            emit combat->targetsChanged();
        }
    }

}

void CombatTracker::modifyCombatants(int attackerIndex, int attackUnit, int attackAmount, bool done, int defenderIndex, int defenderUnit, int defenderAmount)
{
    Combatant* attacker = myCurrentRound[attackerIndex];
    Combatant* defender = (defenderIndex < myTargets.indexOf(attacker))?myTargets[defenderIndex]:myTargets[defenderIndex+1];
    modifyCombatant(attacker,attackUnit,attackAmount,done);
    modifyCombatant(defender, defenderUnit,defenderAmount,false);

    if(defender->isDead()||defender->isIncapacitated())
        defender->deleteLater();
    emit targetsChanged();
    emit currentTicksChanged();
    emit currentRoundChanged();
    emit nextTicksChanged();
    emit nextRoundChanged();
}

QQmlListProperty<Combatant> CombatTracker::currentRound()
{
    if(currentRoundMap.count() > 0  && myCurrentRound != currentRoundMap.values(myCurrentTick))
    {
        myCurrentRound = currentRoundMap.values(myCurrentTick);
    }
    return QQmlListProperty<Combatant>(this,myCurrentRound);
}

QQmlListProperty<Combatant> CombatTracker::nextRound()
{

    if(nextRoundMap.count() > 0  && myNextRound != nextRoundMap.values())
    {
        myNextRound = nextRoundMap.values();
    }
    return QQmlListProperty<Combatant>(this,myNextRound);
}



QVariantList CombatTracker::currentTicks()
{
    QVariantList temp;
    foreach(int num,currentRoundMap.uniqueKeys())
    {
        int index ;
        for( index = 0; index < temp.size() && num < temp[index].toInt();index++);
        temp.insert(index, QVariant(num));
    }
    return temp;
}


QVariantList CombatTracker::nextTicks()
{
    QVariantList temp;
    foreach(int num,nextRoundMap.uniqueKeys())
    {
        int index ;
        for( index = 0; index < temp.size() && num < temp[index].toInt();index++);
        temp.insert(index, QVariant(num));
    }
    return temp;
}

bool CombatTracker::inBattle()
{
    return battleStarted;
}

void CombatTracker::binaryInsertion(QList<Combatant *> *host, Combatant* add, int left, int right)
{
    int mid = (left+right)/2;
    if (right <= left )
    {
        if( mid + 1 < host->count() && add->initiative() < host->at(mid)->initiative())
            host->insert(mid+1,add);
        else
            host->insert(mid,add);
    }
    else
    {
        if (add->initiative() < host->at(mid)->initiative())
            binaryInsertion(host, add, ++mid, right);
        else
            binaryInsertion(host, add, left, --mid);
    }
}


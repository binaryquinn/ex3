#include "combattracker.h"
#include <QDebug>

CombatTracker::CombatTracker(QObject *parent) : QObject(parent)
{
    battleStarted = false;
}

CombatTracker::~CombatTracker()
{

}

void CombatTracker::addCombatant(Combatant *add)
{
    add->joinBattle();

    QList<Combatant *> *host;
    QMap<int, Combatant * > *hostMap;
    if(!battleStarted)
    {
        host = &myCurrentRound;
        hostMap = &currentRoundMap;
    }
    else
    {
        host = &myNextRound;
        hostMap = &nextRoundMap;
    }


    if(host->count() == 0)
        host->append(add);
    else
        binaryInsertion(host,add,0,host->count());

    hostMap->insertMulti(add->initiative(),add);

    if(!battleStarted) emit currentRoundChanged();
    else emit nextRoundChanged();

    myTargets.clear();
    myTargets.append(myCurrentRound);
    myTargets.append(myNextRound);
    if(myTargets.count() > 0)
    {
        myTargets.removeFirst();
        emit targetsChanged();
    }

}
void CombatTracker::attack(int attackerIndex, int attackingWeapon, int defenderIndex, int defendingWeapon, int attackType, int defenseType)
{
    Combatant *attacker = myCurrentRound[attackerIndex];
    Combatant *defender = myTargets[defenderIndex];

    QList<Combatant *> *host = myCurrentRound.contains(defender)? &myCurrentRound : &myNextRound;

    Weapon *aWeapon = attacker->weapon(attackingWeapon);
    Weapon *dWeapon = defender->weapon(defendingWeapon);
    int attackResult = attacker->attack((CombatConstants::Attack)attackType, aWeapon) - defender->defense((CombatConstants::Defense)defenseType, dWeapon);
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

    myTargets.clear();
    myTargets.append(myCurrentRound);
    myTargets.append(myNextRound);
    if(myTargets.count() > 0)
    {
        myTargets.removeFirst();
        emit targetsChanged();
    }


}

void CombatTracker::modifyCombatant(int index, bool current, int unit, int amount, bool done)
{
    Combatant *subject = (current)? myCurrentRound[index] : myTargets[index];
    QList<Combatant *> *host = myCurrentRound.contains(subject)? &myCurrentRound : &myNextRound;

    if(amount != 0)
    {

        if(unit == 0)
            subject->changeInitiative(amount);
        else
            subject->suffer(std::abs(amount),(CombatConstants::Wounds)unit);
    }
    host->removeOne(subject);
    if(done)
    {
        host =  &myNextRound;
    }

    if(!(subject->isDead()||subject->isIncapacitated()))
        binaryInsertion(host, subject,0, host->count());


    if(myCurrentRound.count() < 1)
    {
        myCurrentRound.swap(myNextRound);
    }
    myCurrentRound.first()->refreshTurn();
    emit currentRoundChanged();
    emit nextRoundChanged();

    myTargets.clear();
    myTargets.append(myCurrentRound);
    myTargets.append(myNextRound);
    if(myTargets.count() > 0)
    {
        myTargets.removeFirst();
        emit targetsChanged();
    }

}

QQmlListProperty<Combatant> CombatTracker::currentRound()
{
    return QQmlListProperty<Combatant>(this,myCurrentRound);
}

QQmlListProperty<Combatant> CombatTracker::nextRound()
{
    return QQmlListProperty<Combatant>(this,myNextRound);
}

QQmlListProperty<Combatant> CombatTracker::validTargets()
{
    return QQmlListProperty<Combatant>(this,myTargets);
}

QList<int> CombatTracker::currentTicks()
{
    return currentRoundMap.keys();
}

QQmlListProperty<Combatant> CombatTracker::combatantsOnTick(int tick, CombatConstants::Rounds which)
{
    QList<Combatant*> temp = (which == CombatConstants::Current)?currentRoundMap.values(tick):nextRoundMap.values(tick);
    return QQmlListProperty<Combatant>(this,temp);
}

QList<int> CombatTracker::nextTicks()
{
    return nextRoundMap.keys();
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


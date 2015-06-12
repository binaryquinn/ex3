#include "combattracker.h"

CombatTracker::CombatTracker(QObject *parent) : QObject(parent)
{
    battleStarted = false;
    myActionList  << "Attack (Withering)" << "Attack (Decisive)" << "Full Defense" << "Defend Other" << "Miscellaeneous Attack";
}

CombatTracker::~CombatTracker()
{

}

void CombatTracker::addCombatant(Combatant *add)
{
    add->joinBattle();

    QList<Combatant *> *host;

    if(!battleStarted)
        host = &myCurrentRound;
    else
        host = &myNextRound;



    if(host->count() == 0)
        host->append(add);
    else
       binaryInsertion(host,add,0,host->count());

    if(!battleStarted) emit currentRoundChanged();
    else emit nextRoundChanged();

    myTargets.clear();
    myTargets.append(myCurrentRound);
    myTargets.append(myNextRound);
    if(myTargets.count() > 1)
    {
        myTargets.removeFirst();
        emit targetsChanged();
        emit actionsChanged();
    }

}

void CombatTracker::attack(int attackerIndex, int attackingWeapon, int defenderIndex, int defendingWeapon, int attackType, int defenseType)
{
    Combatant *attacker = myCurrentRound[attackerIndex];
    Combatant *defender = myTargets[defenderIndex];
    Weapon *aWeapon = attacker->weapon(attackingWeapon);
    Weapon *dWeapon = defender->weapon(defendingWeapon);
    int attackResult = attacker->attack((CombatConstants::Attack)attackType, aWeapon) - defender->defense((CombatConstants::Defense)defenseType, dWeapon);

    if(attackResult > 0)
    {
        int damagePool = attacker->damage((CombatConstants::Attack)attackType, aWeapon) + (attackType == CombatConstants::Withering)? attackResult : 0;
        int damageResult = defender->takeDamage((CombatConstants::Attack)attackType,damagePool,aWeapon->overwhelming(),aWeapon->woundType());
        if((CombatConstants::Attack)attackType == CombatConstants::Withering)
            attacker->changeInitiative(1+damageResult);
        else
            attacker->resetInitiative();
    }
    binaryInsertion(&myNextRound,attacker, 0,myNextRound.count());
    myCurrentRound.removeAt(attackerIndex);

    emit currentRoundChanged();
    emit nextRoundChanged();

    myTargets.clear();
    myTargets.append(myCurrentRound);
    myTargets.append(myNextRound);
    if(myTargets.count() > 1)
    {
        myTargets.removeFirst();
        emit targetsChanged();
        emit actionsChanged();
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

QStringList CombatTracker::actions()
{
    if(myCurrentRound.count()> 0)
    {

        if(myCurrentRound[0]->initiative() > 0 && myActionList.count() == 4)
        {
            myActionList.insert(1,"Attack (Decisive)");
            emit actionsChanged();
        }
        else if(myCurrentRound[0]->initiative() < 1 && myActionList.count() == 5)
        {
            myActionList.removeAt(1);
            emit actionsChanged();
        }

        return myActionList;
    }
    return QStringList();
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



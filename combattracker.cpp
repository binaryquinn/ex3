#include "combattracker.h"

CombatTracker::CombatTracker(QObject *parent) : QObject(parent)
{

}

CombatTracker::~CombatTracker()
{

}

void CombatTracker::addCombatant(Combatant *add)
{
    add->joinBattle();

    QList<Combatant *> *host;

    if(!inBattle)
        host = &myCurrentRound;
    else
        host = &myNextRound;



    if(host->count() == 0)
        host->append(add);
    else
       binaryInsertion(host,add,0,host->count()-1);

}

void CombatTracker::attack(Combatant *attacker, int attackingWeapon, Combatant *defender, int defendingWeapon, CombatConstants::Attack attackType, CombatConstants::Defense defenseType)
{
    Weapon *aWeapon = attacker->weapon(attackingWeapon);
    Weapon *dWeapon = defender->weapon(defendingWeapon);
    int attackResult = attacker->attack(attackType, aWeapon) - defender->defense(defenseType, dWeapon);

    if(attackResult > 0)
    {
        int damagePool = attacker->damage(attackType, aWeapon) + (attackType == CombatConstants::Withering) ? attackResult : 0;
        defender->takeDamage(attackType,damagePool,aWeapon->overwhelming(),aWeapon->woundType());
        attacker->resetInitiative();
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

void CombatTracker::add(QString name, int dex, int str,int sta, int wit)
{
    addCombatant(new Combatant(name,dex,str,sta,wit));
}


void CombatTracker::binaryInsertion(QList<Combatant *> *host, Combatant* add, int left, int right)
{
    if (right <= left)
        host->insert(left,add);
    else
    {
        int mid = (left+right)/2;

        if ( add < host->at(mid))
            binaryInsertion(host, add, left, mid - 1);
        else
            binaryInsertion(host, add, mid + 1, right);
    }
}


bool operator <( Combatant &lhs, Combatant &rhs)
{
    return lhs.initiative() < rhs.initiative();
}

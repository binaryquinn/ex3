#include "combattracker.h"

CombatTracker::CombatTracker(QObject *parent) : QObject(parent)
{
    foreach(QString ability,CombatConstants::allAbilities())
        myDialogAbilities.append(new TraitRating(ability,0));

    foreach(QString attributes,CombatConstants::attributes())
        myDialogAttributes.append(new TraitRating(attributes,1));


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

    if(!inBattle) emit currentRoundChanged();
    else emit nextRoundChanged();
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

QQmlListProperty<TraitRating> CombatTracker::attributes()
{
    return QQmlListProperty<TraitRating>(this,myDialogAttributes);
}

QQmlListProperty<TraitRating> CombatTracker::abilities()
{
    return QQmlListProperty<TraitRating>(this,myDialogAbilities);
}

void CombatTracker::add(QString name, int soak,int hardness, int penalty )
{
    int dex = myDialogAttributes[1]->property("stat").toInt();
    int str = myDialogAttributes[0]->property("stat").toInt();
    int sta = myDialogAttributes[2]->property("stat").toInt();
    int wit = myDialogAttributes[3]->property("stat").toInt();
    Combatant * newbie = new Combatant(name,dex,str,sta,wit);
    newbie->setArmor(soak,hardness,penalty);
    addCombatant(newbie);
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


TraitRating::TraitRating(QObject *parent):QObject(parent), myName(""), myRating(0)
{

}

TraitRating::TraitRating(QString name, unsigned int rating, QObject *parent):QObject(parent), myName(name), myRating(rating)
{

}

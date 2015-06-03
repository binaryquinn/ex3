#include "combattracker.h"

CombatTracker::CombatTracker(QObject *parent) : QObject(parent)
{
    foreach(QString ability,CombatConstants::allAbilities())
        myDialogAbilities.append(new TraitRating(ability,0));

    foreach(QString attributes,CombatConstants::attributes())
        myDialogAttributes.append(new TraitRating(attributes,1));

    myActionList  << "Attack (Withering)" << "Attack (Decisive)" << "Full Defense" << "Defend Other" << "Miscellaeneous Attack";
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
       binaryInsertion(host,add,0,host->count());

    if(!inBattle) emit currentRoundChanged();
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

QQmlListProperty<Combatant> CombatTracker::validTargets()
{
    return QQmlListProperty<Combatant>(this,myTargets);
}

QQmlListProperty<TraitRating> CombatTracker::newCombatantAttributes()
{
    return QQmlListProperty<TraitRating>(this,myDialogAttributes);
}

QQmlListProperty<TraitRating> CombatTracker::newCombatantAbilities()
{
    return QQmlListProperty<TraitRating>(this,myDialogAbilities);
}

QQmlListProperty<Weapon> CombatTracker::newCombatantWeapons()
{
    return QQmlListProperty<Weapon>(this, myDialogWeapons);
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

void CombatTracker::add(QString name, int soak,int hardness, int penalty )
{
    int str = myDialogAttributes[0]->property("stat").toInt();
    int dex = myDialogAttributes[1]->property("stat").toInt();
    int sta = myDialogAttributes[2]->property("stat").toInt();
    int wit = myDialogAttributes[3]->property("stat").toInt();
    Combatant * newbie = new Combatant(name,dex,str,sta,wit);
    newbie->setArmor(soak,hardness,penalty);

    foreach (TraitRating* trait, myDialogAbilities)
        newbie->setAbility(trait->property("name").toString(),trait->property("stat").toInt());

    foreach (Weapon * wep, myDialogWeapons)
        newbie->addWeapon(wep);

    addCombatant(newbie);
}

void CombatTracker::addWeapon(QString name, int qual, int weight, QString ability, int damage, int range)
{
    myDialogWeapons.append(new Weapon(name,(Weapon::Quality)qual,(Weapon::WeightClass)weight, ability, (CombatConstants::Wounds)damage, (CombatConstants::Range)range));
    emit weaponsChanged();
}

void CombatTracker::cleanDialog()
{
    int cleaner = 0;

    for(;cleaner < myDialogAttributes.count();cleaner++)
        myDialogAttributes[cleaner]->setProperty("stat",1);

    for(cleaner = 0;cleaner < myDialogAbilities.count();cleaner++)
        myDialogAbilities[cleaner]->setProperty("stat",0);

    myDialogWeapons.clear();

    emit attributesChanged();
    emit abilitiesChanged();
    emit weaponsChanged();

}


void CombatTracker::binaryInsertion(QList<Combatant *> *host, Combatant* add, int left, int right)
{
    int mid = (left+right)/2;
    if (right <= left)
        host->insert(mid,add);
    else
    {
        if (add->initiative() < host->at(mid)->initiative())
            binaryInsertion(host, add, ++mid, right);
        else
            binaryInsertion(host, add, left, --mid);
    }
}


TraitRating::TraitRating(QObject *parent):QObject(parent), myName(""), myRating(0)
{

}

TraitRating::TraitRating(QString name, unsigned int rating, QObject *parent):QObject(parent), myName(name), myRating(rating)
{

}

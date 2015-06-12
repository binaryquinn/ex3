#include "combatant.h"
#include <math.h>
#include <QDebug>


Combatant::Combatant(QObject *parent):QObject(parent), myName(""), myStrength(0), myDexterity(0), myStamina(0), myWits(0), myArmorSoak(0),myHardness(0)
{
    initialize();
}

Combatant::Combatant(QString name, int str, int dex, int sta, int wit, QObject *parent):
    QObject(parent), myName(name), myStrength(str), myDexterity(dex), myStamina(sta), myWits(wit), myArmorSoak(0), myHardness(0)
{
    initialize();
}



void Combatant::setHealth(QList<int> HLCounts)
{
    if(HLCounts.size() != 5)
        return;

    for(int hLevel = 0; hLevel < HLCounts.size(); hLevel++)
        myHealth.setHealthLevel(hLevel, HLCounts[hLevel]);
}

void Combatant::setArmor(int soak, int hardness, int penalty)
{
    myArmorSoak = soak;
    myHardness = hardness;
    myMobilityPenalty = penalty;
}

int Combatant::joinBattle()
{
    myInitiative = 3 + D10::roll(std::max(myWits + myCombatAbilities["Awareness"],0));
    return myInitiative;
}

QList<int> Combatant::armor()
{
    QList<int> myArmor;
    myArmor << myArmorSoak << myHardness << myMobilityPenalty;
    return myArmor;
}

int Combatant::attack(CombatConstants::Attack attackType, Weapon * selectedWeapon)
{
    if(attackType == CombatConstants::Withering)
        return D10::roll(std::max(myDexterity + myCombatAbilities[selectedWeapon->ability()] + selectedWeapon->accuracy() - myHealth.currentPenalty(),0));
    return D10::roll(std::max(myDexterity + myCombatAbilities[selectedWeapon->ability()]- myHealth.currentPenalty(),0));
}


int Combatant::damage(CombatConstants::Attack attackType, Weapon *selectedWeapon)
{
    if(attackType == CombatConstants::Withering)
        return myStrength + selectedWeapon->damage();
    return myInitiative;
}

int Combatant::defense(CombatConstants::Defense defenseType, Weapon *weapon, bool onslaught)
{
    int value;
    int parryDef =  parryDefense(weapon);
    int evasion = ceil((double)(myDexterity+myCombatAbilities["Dodge"])/2) - myMobilityPenalty;;
    switch(defenseType)
    {
        case CombatConstants::Overall: value = (evasion > parryDef) ? evasion : parryDef; break;
        case CombatConstants::Evasion: value = evasion; break;
        default: value = parryDef; break;
    };
    value -= myHealth.currentPenalty();
    value -= myOnslaught;
    if(onslaught)
        myOnslaught++;
    value = std::max(value,0);
    return value;
}

void Combatant::refreshTurn()
{
    myOnslaught = 0;
    if(myCrashCounter == 3)
        resetInitiative();
    if(myInitiative < 1)
        myCrashCounter++;
    else
        myCrashCounter = 0;


}

void Combatant::resetInitiative()
{
    myInitiative = 3;
    myCrashCounter = 0;
    emit initiativeChanged();
}

void Combatant::changeInitiative(int value)
{
    myInitiative += value;
    emit initiativeChanged();
}

int Combatant::initiative()
{
    return myInitiative;
}

int Combatant::takeDamage(CombatConstants::Attack attackType, int damage, int overwhelming, CombatConstants::Wounds damageType)
{


    if(attackType == CombatConstants::Withering)
    {
       int postSoak = damage - (myStamina + myArmorSoak); //calculating dice pool
       if(postSoak < overwhelming)
           postSoak = overwhelming;
       postSoak = D10::roll(postSoak); //dice pool becomes dice successes
       myInitiative -= postSoak;
       emit initiativeChanged();
       return postSoak;
    }
    else
    {
        if( myInitiative < 1 || myHardness < damage)
        {
            int wounds = D10::roll(damage,false);
            myHealth.takeDamage(wounds, damageType);
            return wounds;
        }
    }
    return 0;
}

void Combatant::setAbility(QString name, int value)
{
    if(myCombatAbilities.contains(name))
        myCombatAbilities[name] = value;
}




Weapon *Combatant::weapon(int selected)
{
    return myPanoply[selected];
}

void Combatant::addWeapon(Weapon *addition)
{
    myPanoply.append(addition);
}

QStringList Combatant::weaponry()
{
    QStringList weaponNames;
    foreach(Weapon * weapon, myPanoply)
    {
        weaponNames.append(weapon->name());
    }
    return weaponNames;
}

QString Combatant::name() const
{
    return myName;
}
int Combatant::stamina() const
{
    return myStamina;
}

QStringList Combatant::defenseList()
{
    QStringList defList;
    defList << QString("Evade: %1 Defense ").arg(defense(CombatConstants::Evasion,myPanoply[0],false));

    foreach(Weapon* weaponCheck, myPanoply)
    {
        defList << QString::fromLatin1("Parry with %1: %2 Defense").arg(weaponCheck->name()).arg(defense(CombatConstants::Parry,weaponCheck, false));
    }
    return defList;
}


void Combatant::initialize()
{

    myOnslaught = 0;
    QStringList abilist = CombatConstants::allAbilities();
    foreach(QString ability , abilist)
        myCombatAbilities.insert(ability,0);
}

int Combatant::parryDefense(Weapon *weapon)
{
    int ability = myCombatAbilities.contains(weapon->ability()) ? myCombatAbilities[weapon->ability()] : 0;
    return ceil((double)(myDexterity + ability)/2) + weapon->defense();
}

int D10::roll(int dieCount, bool dblSuccess, int dblThreshold)
{

    int successes = 0;
    int dieValue = 0;
    for (int die = 0; die < dieCount; die++)
    {

        dieValue = (std::rand()%10)+1;
        if(dieValue > 6 )
            successes++;
        if(dblSuccess)
        {
            if(dieValue >= dblThreshold)
                successes++;
        }
    }
    return successes;
}

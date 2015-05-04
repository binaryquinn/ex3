#include "combatant.h"


Combatant::Combatant(QObject *parent):QObject(parent), myName(""), myJoinBattle(0), myDexterity(0), myStrength(0), myNaturalSoak(0), myArmorSoak(0),myHardness(0)
{
    initialize();
}

Combatant::Combatant(QString name, int join, int dex, int str, int nSoak, int aSoak, int hard, QObject *parent):
    QObject(parent), myName(name), myJoinBattle(join), myDexterity(dex), myStrength(str), myNaturalSoak(nSoak), myArmorSoak(aSoak),myHardness(hard)
{
    initialize();
}



void Combatant::setHealth(QList<int> HLCounts)
{
    if(HLCounts.size() != 5)
        return;

    myHealthLevels.clear();

    for(int index = 0;index < 5;index++)
    {
        myHealthLevels.append(QList<int>());
        for(int count = 0; count < HLCounts[index];count++)
            myHealthLevels[index] << 0;
    }
}

int Combatant::joinBattle()
{
    myInitiative = 3 + D10::roll(myJoinBattle);
    return myInitiative;
}

int Combatant::attack(CombatConstants::Attack attackType, Weapon * selectedWeapon)
{
    if(attackType == CombatConstants::Withering)
        return D10::roll(myDexterity + myCombatAbilities[selectedWeapon->ability()] + selectedWeapon->accuracy());
    return D10::roll(myDexterity + myCombatAbilities[selectedWeapon->ability()]);
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
    int evasion = (myDexterity+myCombatAbilities["Dodge"])/2;
    switch(defenseType)
    {
        case CombatConstants::Overall: value = (evasion > parryDef) ? evasion : parryDef; break;
        case CombatConstants::Evasion: value = evasion; break;
        default: value = parryDef; break;
    };
    value -= myOnslaught;
    if(onslaught)
        myOnslaught++;
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
}

void Combatant::changeInitiative(int value)
{
    myInitiative += value;
}

int Combatant::initiative()
{
    return myInitiative;
}

int Combatant::takeDamage(CombatConstants::Attack attackType, int damage, int overwhelming, CombatConstants::Wounds damageType)
{


    if(attackType == CombatConstants::Withering)
    {
       int postSoak = damage - (myNaturalSoak + myArmorSoak); //calculating dice pool
       if(postSoak < overwhelming)
           postSoak = overwhelming;
       postSoak = D10::roll(postSoak); //dice pool becomes dice successes
       myInitiative -= postSoak;
       return postSoak;
    }
    else
    {
        if( myInitiative < 1 || myHardness < damage)
        {
            int wounds = D10::roll(damage,false);
            if(damageType == CombatConstants::Bashing)
                for(int count = wounds; count > 0; count--)
                {
                    //if there's a wound slot left, fill it with bashing
                    if(bashingEnd.second  < myHealthLevels[bashingEnd.first].count() && bashingEnd.first < myHealthLevels.count())
                  {      myHealthLevels[bashingEnd.first][bashingEnd.second] = CombatConstants::Bashing;
                    if((bashingEnd.second + 1) < myHealthLevels[bashingEnd.first].count())
                    {
                        bashingEnd.second++;
                    }
                    else if(bashingEnd.first < myHealthLevels.count())
                    {
                        bashingEnd.first++;
                        bashingEnd.second = 0;
                    }
                    }
                    //if there're still wounds after filling the incapacitated slot with bashing, start converting bashing to lethal
                }
                return wounds;
        }
    }
    return 0;
}




Weapon *Combatant::weapon(int selected)
{
    return equippedWeapons[selected];
}

void Combatant::addWeapon(Weapon *addition, bool equipped)
{
    myPanoply.append(addition);
    if(equipped)
    {

    }
}


void Combatant::initialize()
{

    myOnslaught = 0;
    QList<int> defaultHealth;
    defaultHealth << 1 << 2 << 2 << 1 <<1;
    setHealth(defaultHealth);
    bashingEnd = lethalEnd = aggravatedEnd = QPair<int,int> (0,0);
}

int Combatant::parryDefense(Weapon *weapon)
{
    int ability = myCombatAbilities.contains(weapon->ability()) ? myCombatAbilities[weapon->ability()] : 0;
    return (myDexterity + ability)/2 + weapon->defense();
}





Weapon::Weapon(QObject *parent):QObject(parent), myAccuracy(0), myDamage(0), myDefense(0), myAbility(""), myStrength(0),
        myWoundType(CombatConstants::None), myOverwhelming(0), myRange(CombatConstants::Close), myHanded(false)
{

}

Weapon::Weapon(QString name, int acc, int dmg, int def, QString abi, bool useStr, CombatConstants::Wounds type, int over,CombatConstants::Range range,bool handed, QObject *parent):
         QObject(parent), myName(name), myAccuracy(acc), myDamage(dmg), myDefense(def), myAbility(abi), myStrength(useStr), myWoundType(type), myOverwhelming(over), myRange(range),myHanded(handed)
{

}


int Weapon::accuracy() const
{
    return myAccuracy;
}

void Weapon::setAccuracy(int value)
{
    myAccuracy = value;
}
int Weapon::damage() const
{
    return myDamage;
}

void Weapon::setDamage(int value)
{
    myDamage = value;
}
int Weapon::defense() const
{
    return myDefense;
}

void Weapon::setDefense(int value)
{
    myDefense = value;
}
QString Weapon::ability() const
{
    return myAbility;
}

void Weapon::setAbility(const QString &value)
{
    myAbility = value;
}
bool Weapon::usesStrength() const
{
    return myStrength;
}

void Weapon::setUsesStrength(bool value)
{
    myStrength = value;
}
CombatConstants::Wounds Weapon::woundType() const
{
    return myWoundType;
}

void Weapon::setWoundType(CombatConstants::Wounds value)
{
    myWoundType = value;
}
int Weapon::overwhelming() const
{
    return myOverwhelming;
}

void Weapon::setOverwhelming(int value)
{
    myOverwhelming = value;
}
QString Weapon::name() const
{
    return myName;
}

void Weapon::setName(const QString &value)
{
    myName = value;
}
CombatConstants::Range  Weapon::range() const
{
    return myRange;
}

void Weapon::setRange(CombatConstants::Range  value)
{
    myRange = value;
}
bool Weapon::is2Handed() const
{
    return myHanded;
}

void Weapon::set2Handed(bool value)
{
    myHanded = value;
}





int D10::roll(int dieCount, bool dblSuccess, int dblThreshold)
{
    int successes = 0;
    int dieValue = 0;
    for (int die = 0; die < dieCount; die++)
    {
        dieValue = (qrand() % 10) + 1;

        if(dieValue > 6)
            successes++;
        if(dblSuccess)
        {
            if(dieValue >= dblThreshold)
                successes++;
        }
    }
    return successes;
}


QStringList CombatConstants::combatAbilities()
{
    if(myAttackAbilities.empty())
    {
        myAttackAbilities << "Archery" << "Brawl" << "Martial Arts" << "Melee"<< "Thrown";
    }
    return myAttackAbilities;
}

QStringList CombatConstants::allAbilities()
{
    if(myOtherAbilities.empty())
        myOtherAbilities << "Athletics" << "Awareness" << "Dodge"  << "Resistance" << "Ride" ;
    QStringList bothLists;
    bothLists << myOtherAbilities << combatAbilities();
    bothLists.sort();
    return bothLists;


}

QStringList CombatConstants::ranges()
{
    if(myRanges.empty())
    {
        myRanges<< "Close" << "Short" << "Medium" << "Long"<< "Extreme";
    }
    return myRanges;
}

QStringList CombatConstants::damageTypes()
{
    if(myDamageTypes.empty())
    {
        myDamageTypes<< "Bashing" << "Lethal" << "Aggravated";
    }
    return myDamageTypes;
}


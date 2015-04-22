#include "combatant.h"


Combatant::Combatant(QObject *parent):QObject(parent), myName(""), myEvasion(0), myParry(0), myJoinBattle(0), myDexterity(0), myStrength(0), myNaturalSoak(0), myArmorSoak(0),myHardness(0)
{
    initialize();
}

Combatant::Combatant(QString name, int eva, int par, int join, int dex, int str, int nSoak, int aSoak, int hard, QObject *parent):
    QObject(parent), myName(name), myEvasion(eva), myParry(par), myJoinBattle(join), myDexterity(dex), myStrength(str), myNaturalSoak(nSoak), myArmorSoak(aSoak),myHardness(hard)
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

int Combatant::attack(int attackType)
{
    if(attackType == Withering)
        return D10::roll(myDexterity + myCombatAbility.second + myWeapon.accuracy());
    return D10::roll(myDexterity + myCombatAbility.second);
}


int Combatant::damage(int attackType)
{
    if(attackType == Withering)
        return myStrength + myWeapon.damage();
    return myInitiative;
}

int Combatant::defense(DefenseType which, bool onslaught)
{
    int value;
    switch(which)
    {
        case Overall: value = (myEvasion > myParry)? myEvasion:myParry;break;
        case Evasion: value = myEvasion;break;
        case Parry: value = myParry;break;
    };
    value -= myOnslaught;
    if(onslaught)
        myOnslaught++;
    return value;
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

int Combatant::takeDamage(int attackType, int damage, int overwhelming, int damageType)
{


    if(attackType == Withering)
    {
       int postSoak = D10::roll(damage) - (myNaturalSoak + myArmorSoak);
       if(postSoak<overwhelming)
           postSoak = overwhelming;
       myInitiative -= postSoak;
       return postSoak;
    }
    else
    {
        if(myHardness < damage)
        {
            int wounds = D10::roll(damage,false);
            if(damageType == WoundType::Bashing)
                for(int count = wounds; count > 0; count--)
                {
                    //if there's a wound slot left, fill it with bashing
                    if(bashingEnd.second  < myHealthLevels[bashingEnd.first].count() && bashingEnd.first < myHealthLevels.count())
                  {      myHealthLevels[bashingEnd.first][bashingEnd.second] = WoundType::Bashing;
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

void Combatant::initialize()
{
    myOnslaught = 0;
    QList<int> defaultHealth;
    defaultHealth << 1 << 2 << 2 << 1 <<1;

    bashingEnd = lethalEnd = aggravatedEnd = QPair<int,int> (0,0);
}





Weapon::Weapon(QObject *parent):QObject(parent), myAccuracy(0), myDamage(0), myDefense(0), myAbility(""), myStrength(0), myWoundType(0), myOverwhelming(0)
{

}

Weapon::Weapon(int acc, int dmg, int def, QString abi, bool useStr, int type, int over, QObject *parent):
     QObject(parent), myAccuracy(acc), myDamage(dmg), myDefense(def), myAbility(abi), myStrength(useStr), myWoundType(type), myOverwhelming(over)
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
int Weapon::woundType() const
{
    return myWoundType;
}

void Weapon::setWoundType(int value)
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

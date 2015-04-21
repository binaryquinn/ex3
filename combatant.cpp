#include "combatant.h"

Combatant::Combatant()
{

}

Combatant::~Combatant()
{

}

int Combatant::attack(int attackType)
{
    if(attackType == AttackType::Withering)
        return myDexterity + myCombatAbility.second + myWeapon.accuracy();
    return myDexterity + myCombatAbility.second;
}


int Combatant::damage(int attackType)
{
    if(attackType == AttackType::Withering)
        return myStrength + myWeapon.damage();
    return myInitiative;
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


    if(attackType == AttackType::Withering)
    {
       int postSoak = damage - (myNaturalSoak + myArmorSoak);
       if(postSoak<overwhelming)
           postSoak = overwhelming;
       myInitiative -= postSoak;
       return postSoak;
    }
    else
    {
        if(myHardness < damage)
        ; //take damage on the health track

    }
    return 0;
}





Weapon::Weapon()
{

}

Weapon::~Weapon()
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
    return usesStrength;
}

void Weapon::setUsesStrength(bool value)
{
    usesStrength = value;
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








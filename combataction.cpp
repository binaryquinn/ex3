#include "combataction.h"

CombatAction::CombatAction(QObject *parent) : QObject(parent), myName(""),canFlurry(false), isRolled(false), whenCrashed(false), weaponUsed(false), isDecisive(false), myTarget(CombatConstants::Self), myDifficulty(QVariant())
{

}

CombatAction::CombatAction(QString name, bool flurry, bool rolled, bool crashed, bool weapon, bool decisive, CombatConstants::Targetting target, QVariant difficulty, QObject *parent)
    : QObject(parent), myName(name),canFlurry(flurry), isRolled(rolled), whenCrashed(crashed), weaponUsed(weapon), isDecisive(decisive), myTarget(target), myDifficulty(difficulty)
{

}

QString CombatAction::getName() const
{
    return myName;
}
bool CombatAction::canFlurryThis() const
{
    return canFlurry;
}
bool CombatAction::isRolledAction() const
{
    return isRolled;
}
bool CombatAction::canUseWhenCrashed() const
{
    return whenCrashed;
}
CombatConstants::Targetting CombatAction::getTargetting() const
{
    return myTarget;
}

void CombatAction::addPool(QString attribute, QString ability)
{
    myPools.append( QPair<QString,QString>(attribute, ability));
}

QPair<QString, QString> CombatAction::getPool(CombatAction::Pool which)
{
    if(which > myPools.count())
        return QPair<QString, QString> ();
    return myPools[which];
}

bool CombatAction::decisiveAction() const
{
    return isDecisive;
}

bool CombatAction::isWeaponUsed() const
{
    return weaponUsed;
}








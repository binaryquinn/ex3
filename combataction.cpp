#include "combataction.h"

CombatAction::CombatAction(QObject *parent) : QObject(parent), myName(""),canFlurry(false), isRolled(false), whenCrashed(false), myTarget(CombatConstants::Self)
{

}

CombatAction::CombatAction(QString name, bool flurry, bool rolled, bool crashed, CombatConstants::Targetting target, QObject *parent)
    : QObject(parent), myName(name),canFlurry(flurry), isRolled(rolled), whenCrashed(crashed), myTarget(target)
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







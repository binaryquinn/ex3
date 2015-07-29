#ifndef COMBATACTION_H
#define COMBATACTION_H

#include <QObject>
#include "combatconstants.h"

class CombatAction : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName CONSTANT)
    Q_PROPERTY(bool flurriable READ canFlurryThis CONSTANT)
    Q_PROPERTY(bool rolledAction READ isRolledAction CONSTANT)
    Q_PROPERTY(bool duringCrash READ canUseWhenCrashed CONSTANT)
    Q_PROPERTY(CombatConstants::Targetting getTargetting READ getTargetting CONSTANT)

public:
    explicit CombatAction(QObject *parent = 0);
    CombatAction(QString name, bool flurry, bool rolled, bool crashed, CombatConstants::Targetting target, QObject *parent = 0);

    QString getName() const;
    bool canFlurryThis() const;
    bool isRolledAction() const;
    bool canUseWhenCrashed() const;
    CombatConstants::Targetting getTargetting() const;

signals:

public slots:

private:
    QString myName;
    bool canFlurry;
    bool isRolled;
    bool whenCrashed;
    CombatConstants::Targetting myTarget;
};

#endif // COMBATACTION_H

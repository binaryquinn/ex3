#ifndef COMBATACTION_H
#define COMBATACTION_H

#include <QObject>
#include "combatconstants.h"
#include <QPair>
#include <QString>
#include <QVariant>

class CombatAction : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName CONSTANT)
    Q_PROPERTY(bool flurriable READ canFlurryThis CONSTANT)
    Q_PROPERTY(bool rolledAction READ isRolledAction CONSTANT)
    Q_PROPERTY(bool duringCrash READ canUseWhenCrashed CONSTANT)
    Q_PROPERTY(bool usesWeapon READ isWeaponUsed CONSTANT)
    Q_PROPERTY(bool decisive READ decisiveAction CONSTANT)
    Q_PROPERTY(QVariant difficulty MEMBER myDifficulty CONSTANT)
    Q_PROPERTY(CombatConstants::Targetting targetting READ getTargetting CONSTANT)
    Q_PROPERTY(bool contested READ isContested CONSTANT)

public:
    explicit CombatAction(QObject *parent = 0);
    CombatAction(QString name, bool flurry, bool rolled, bool crashed, bool weapon, bool decisive, CombatConstants::Targetting target, QVariant difficulty, QObject *parent = 0);

    enum Pool{ Proactive, Reactive};
    Q_ENUMS(Pool)

    QString getName() const;
    bool canFlurryThis() const;
    bool isRolledAction() const;
    bool canUseWhenCrashed() const;
    bool isWeaponUsed() const;
    CombatConstants::Targetting getTargetting() const;
    void addPool(QString attribute, QString ability);
    QPair<QString,QString> getPool(CombatAction::Pool which);
    bool decisiveAction() const;
    bool isContested() const;

signals:

public slots:

private:
    QString myName;
    bool canFlurry;
    bool isRolled;
    bool whenCrashed;
    bool weaponUsed;
    bool isDecisive;
    CombatConstants::Targetting myTarget;
    QVariant myDifficulty;
    QList<QPair<QString, QString> > myPools;
};

#endif // COMBATACTION_H

#ifndef COMBATCONSTANTS_H
#define COMBATCONSTANTS_H

#include <QObject>
#include <QStringList>


Q_DECLARE_METATYPE(QStringList)
class CombatConstants: public QObject
{

    Q_OBJECT
    Q_PROPERTY(QStringList combatAbilities READ combatAbilities CONSTANT)
    Q_PROPERTY(QStringList allAbilities READ allAbilities CONSTANT)
    Q_PROPERTY(QStringList ranges READ ranges CONSTANT)
    Q_PROPERTY(QStringList damageTypes READ damageTypes CONSTANT)
    Q_PROPERTY(QStringList attributes READ attributes CONSTANT)
    Q_PROPERTY(QStringList units READ units CONSTANT)
    Q_PROPERTY(QStringList verbs READ verbs CONSTANT)
    Q_PROPERTY(QStringList actions READ actions CONSTANT)

public:

    enum Wounds{None, Bashing, Lethal, Aggravated};
    Q_ENUMS(Wounds)
    enum Attack{Withering, Decisive};
    Q_ENUMS(Attack)
    enum Defense{Overall, Evasion, Parry};
    Q_ENUMS(Defense)
    enum Range{Close, Short, Medium, Long, Extreme};
    Q_ENUMS(Range)
    enum Actions{Aim, AttackDecisive, AttackWithering, Delay, DefendOther, Disengage, Flurry, FullDefense, Miscellaneous, Move, RiseFromProne, Rush, TakeCover, Withdraw};
    Q_ENUMS(Actions)
    enum Rounds{Current, Next};
    Q_ENUMS(Rounds)
    enum Targetting{Self, Other, Any};
    Q_ENUMS(Targetting)


public slots:
    static QStringList combatAbilities();
    static QStringList allAbilities();
    static QStringList ranges();
    static QStringList damageTypes();
    static QStringList attributes();
    static QStringList units();
    static QStringList verbs();
    static  QStringList actions();


private:
    static QStringList myAttackAbilities;
    static QStringList myOtherAbilities;
    static QStringList myRanges;
    static QStringList myDamageTypes;
    static QStringList myAttributes;
    static QStringList myUnits;
    static QStringList myVerbs;
    static QStringList myActions;

};

#endif // COMBATCONSTANTS_H
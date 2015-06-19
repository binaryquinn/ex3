#ifndef COMBATCONSTANTS_H
#define COMBATCONSTANTS_H

#include <QObject>
#include <QStringList>

Q_DECLARE_METATYPE(QStringList)
class CombatConstants: public QObject
{

    Q_OBJECT
    Q_ENUMS(Wounds)
    Q_ENUMS(Attack)
    Q_ENUMS(Defense)
    Q_ENUMS(Range)
    Q_ENUMS(Hands)
    Q_ENUMS(Rounds)
    Q_PROPERTY(QStringList combatAbilities READ combatAbilities CONSTANT)
    Q_PROPERTY(QStringList allAbilities READ allAbilities CONSTANT)
    Q_PROPERTY(QStringList ranges READ ranges CONSTANT)
    Q_PROPERTY(QStringList damageTypes READ damageTypes CONSTANT)
    Q_PROPERTY(QStringList attributes READ attributes CONSTANT)
    Q_PROPERTY(QStringList units READ units CONSTANT)
    Q_PROPERTY(QStringList verbs READ verbs CONSTANT)

public:

    enum Wounds{None, Bashing, Lethal, Aggravated};
    enum Attack{Withering, Decisive};
    enum Defense{Overall, Evasion, Parry};
    enum Range{Close, Short, Medium, Long, Extreme};
    enum Hands{Left, Right, Both};
    enum Rounds{Current, Next};


public slots:
    static QStringList combatAbilities();
    static QStringList allAbilities();
    static QStringList ranges();
    static QStringList damageTypes();
    static QStringList attributes();
    static QStringList units();
    static QStringList verbs();

signals:
    void combatAbilitiesChanged();
    void allAbilitiesChanged();
    void rangesChanged();

private:
    static QStringList myAttackAbilities;
    static QStringList myOtherAbilities;
    static QStringList myRanges;
    static QStringList myDamageTypes;
    static QStringList myAttributes;
    static QStringList myUnits;
    static QStringList myVerbs;

};

#endif // COMBATCONSTANTS_H
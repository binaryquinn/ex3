#ifndef COMBATANT_H
#define COMBATANT_H

#include <QList>
#include <QObject>
#include <QPair>
#include <QString>


class WoundType: public QObject
{
    Q_OBJECT
    Q_ENUMS(damage)
public:
    enum damage{Bashing = 1, Lethal, Aggravated};
};
class Weapon:public QObject
{
public:
    Weapon();
    ~Weapon();
    int accuracy() const;
    void setAccuracy(int value);

    int damage() const;
    void setDamage(int value);

    int defense() const;
    void setDefense(int value);

    QString ability() const;
    void setAbility(const QString &value);

    bool usesStrength() const;
    void setUsesStrength(bool value);

    int woundType() const;
    void setWoundType(int value);

    int overwhelming() const;
    void setOverwhelming(int value);

private:
    QString myName;
    int myAccuracy;
    int myDamage;
    int myWoundType;
    int myDefense;
    int myOverwhelming;
    QString myAbility;
    bool usesStrength;
};



class Combatant:public QObject
{
    Q_OBJECT
    Q_ENUMS(AttackType)
public:
    Combatant();
    ~Combatant();

    enum AttackType{Withering, Decisive};

    int attack(int attackType);
    int damage(int attackType);

    void resetInitiative();
    void changeInitiative(int value);
    int initiative();

    int takeDamage(int attackType, int damage, int overwhelming, int damageType);

private:
    QString myName;
    int myInitiative;
    QList<QList<int> > myHealthLevels;
    int myEvasion;
    int myParry;
    int myHardness;
    int myJoinBattle;
    int myDexterity;
    int myStrength;
    QPair<QString,int> myCombatAbility;
    Weapon myWeapon;
    int myNaturalSoak;
    int myArmorSoak;
    int Hardness;
};

#endif // COMBATANT_H

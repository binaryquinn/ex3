#ifndef COMBATANT_H
#define COMBATANT_H

#include <QList>
#include <QMap>
#include <QObject>
#include <QPair>
#include <QString>


class D10
{
public:
    static int roll(int dieCount, bool dblSuccess = true, int dblThreshold = 10 );

};

class WoundType: public QObject
{
    Q_OBJECT
    Q_ENUMS(Wounds)
public:
    enum Wounds{Bashing = 1, Lethal, Aggravated};
};

class Weapon:public QObject
{
        Q_OBJECT
public:
    explicit Weapon(QObject *parent = 0);
    Weapon(QString name, int acc, int dmg, int def, QString abi, bool useStr,int type = WoundType::Bashing, int over = 0, QObject* parent = 0);

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

    QString name() const;
    void setName(const QString &value);

private:
    QString myName;
    int myAccuracy;
    int myDamage;
    int myDefense;
    QString myAbility;
    bool myStrength;
    int myWoundType;
    int myOverwhelming;
};



class Combatant:public QObject
{
    Q_OBJECT
    Q_ENUMS(AttackType)
    Q_ENUMS(DefenseType)
public:
    explicit Combatant(QObject *parent = 0);
    Combatant(QString name, int eva, int join, int dex, int str, int nSoak, int aSoak, int hard, QObject *parent = 0);

    void setHealth(QList <int> HLCounts);

    enum AttackType{Withering, Decisive};
    enum DefenseType{Overall,Evasion,Parry};

    int joinBattle();

    int attack(int attackType, Weapon *selectedWeapon);
    int damage(int attackType, Weapon *selectedWeapon);
    int defense(int defenseType, Weapon *weapon, bool onslaught = true);
    void refreshTurn();
    void resetInitiative();
    void changeInitiative(int value);
    int initiative();
    int takeDamage(int attackType, int damage, int overwhelming, int damageType);

    Weapon *weapon(int selected);

private:
    QString myName;
    int myInitiative;
    QList<QList<int> >myHealthLevels;
    int myEvasion;
    int myJoinBattle;
    int myDexterity;
    int myStrength;
    QMap<QString,int> myCombatAbilities;
    QList<Weapon *> myPanoply;
    QList<Weapon *> equippedWeapons;
    int myNaturalSoak;
    int myArmorSoak;
    int myHardness;
    int myOnslaught;
    QPair<int,int> bashingEnd;
    QPair<int,int> lethalEnd;
    QPair<int,int> aggravatedEnd;


    int myCrashCounter;
    void initialize();
    int parryDefense(Weapon *weapon);

};

#endif // COMBATANT_H

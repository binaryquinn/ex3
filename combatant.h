#ifndef COMBATANT_H
#define COMBATANT_H

#include <QList>
#include <QMap>
#include <QObject>
#include <QPair>
#include <QString>
#include <QQmlListProperty>
#include "combatconstants.h"

class D10
{
public:
    static int roll(int dieCount, bool dblSuccess = true, int dblThreshold = 10 );

};


class Weapon:public QObject
{
        Q_OBJECT
public:
    explicit Weapon(QObject *parent = 0);
    Weapon(QString name, int acc, int dmg, int def, QString abi, bool useStr,
           CombatConstants::Wounds type = CombatConstants::Bashing, int over = 0, CombatConstants::Range range = CombatConstants::Close, bool handed = false, QObject* parent = 0);

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

    CombatConstants::Wounds woundType() const;
    void setWoundType(CombatConstants::Wounds value);

    int overwhelming() const;
    void setOverwhelming(int value);

    QString name() const;
    void setName(const QString &value);

    CombatConstants::Range  range() const;
    void setRange(CombatConstants::Range  value);

    bool is2Handed() const;
    void set2Handed(bool value);

private:
    QString myName;
    int myAccuracy;
    int myDamage;
    int myDefense;
    QString myAbility;
    bool myStrength;
    CombatConstants::Wounds myWoundType;
    int myOverwhelming;
    CombatConstants::Range  myRange;
    bool myHanded;
};



class Combatant:public QObject
{

    Q_OBJECT
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(int initiative READ initiative NOTIFY initiativeChanged)
    Q_PROPERTY(QList<int> armor READ armor NOTIFY armorChanged)
    Q_PROPERTY(int stamina READ stamina NOTIFY staminaChanged)
public:
    explicit Combatant(QObject *parent = 0);
    Combatant(QString name, int dex, int str, int sta, int wit, QObject *parent = 0);

    void setHealth(QList <int> HLCounts);
    void setArmor(int soak, int hardness, int penalty);
    int joinBattle();
    QList<int> armor();
    int attack(CombatConstants::Attack attackType, Weapon *selectedWeapon);
    int damage(CombatConstants::Attack attackType, Weapon *selectedWeapon);
    int defense(CombatConstants::Defense defenseType, Weapon *weapon, bool onslaught = true);
    void refreshTurn();
    void resetInitiative();
    void changeInitiative(int value);
    int initiative();
    int takeDamage(CombatConstants::Attack attackType, int damage, int overwhelming, CombatConstants::Wounds damageType);
    void setAbility(QString name, int value);
    Weapon *weapon(int selected);
    void addWeapon(Weapon *addition);
    QString name() const;

    int stamina() const;

signals:
    void nameChanged();
    void initiativeChanged();
    void staminaChanged();
    void armorChanged();

private:
    QString myName;
    int myInitiative;
    QList<QList<int> >myHealthLevels;
    int myStrength;
    int myDexterity;
    int myStamina;
    int myWits;
    QMap<QString,int> myCombatAbilities;
    QList<Weapon *> myPanoply;
    QList<Weapon *> equippedWeapons;
    int myArmorSoak;
    int myHardness;
    int myMobilityPenalty;
    int myOnslaught;
    QPair<int,int> bashingEnd;
    QPair<int,int> lethalEnd;
    QPair<int,int> aggravatedEnd;


    int myCrashCounter;
    void initialize();
    int parryDefense(Weapon *weapon);

};

#endif // COMBATANT_H









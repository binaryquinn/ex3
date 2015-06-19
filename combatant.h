#ifndef COMBATANT_H
#define COMBATANT_H

#include <QList>
#include <QMap>
#include <QObject>
#include <QPair>
#include <QString>
#include <QQmlListProperty>
#include "combatconstants.h"
#include "healthtrack.h"
#include "weapon.h"

class D10
{
public:
    static int roll(int dieCount, bool dblSuccess = true, int dblThreshold = 10 );
};

class Combatant:public QObject
{

    Q_OBJECT
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(int initiative READ initiative NOTIFY initiativeChanged)
    Q_PROPERTY(QList<int> armor READ armor NOTIFY armorChanged)
    Q_PROPERTY(int stamina READ stamina NOTIFY staminaChanged)
    Q_PROPERTY(QStringList weaponry READ weaponry  NOTIFY weaponryChanged)
    Q_PROPERTY(QStringList defenseList READ defenseList NOTIFY defensesChanged)
    Q_PROPERTY(int woundPenalty READ woundPenalty NOTIFY penaltyChanged)
    Q_PROPERTY(QStringList actions READ actions NOTIFY actionsChanged)

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
    void suffer(int amount, CombatConstants::Wounds damageType);
    int takeDamage(CombatConstants::Attack attackType, int damage, int overwhelming, CombatConstants::Wounds damageType);
    void setAbility(QString name, int value);
    Weapon *weapon(int selected);
    void addWeapon(Weapon *addition);
    QStringList weaponry();
    QString name() const;

    int stamina() const;
    QStringList defenseList();
    int woundPenalty();
    bool isIncapacitated();
    bool isDead();
    QStringList actions();

signals:
    void nameChanged();
    void initiativeChanged();
    void staminaChanged();
    void armorChanged();
    void weaponryChanged();
    void defensesChanged();
    void penaltyChanged();
    void actionsChanged();

private:
    QString myName;
    int myInitiative;
    HealthTrack myHealth;
    int myStrength;
    int myDexterity;
    int myStamina;
    int myWits;
    QMap<QString,int> myCombatAbilities;
    QList<Weapon *> myPanoply;
    int myArmorSoak;
    int myHardness;
    int myMobilityPenalty;
    int myOnslaught;
    int myCrashCounter;
    QStringList myActionList;
    void initialize();
    int parryDefense(Weapon *weapon);
    int myCrashGuard;
};

#endif // COMBATANT_H



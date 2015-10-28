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
#include <QQmlListProperty>
#include "combataction.h"



Q_DECLARE_METATYPE(QList<CombatAction*>)
Q_DECLARE_METATYPE(QList<Weapon*>)
class Combatant:public QObject
{

    Q_OBJECT
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(int initiative READ initiative NOTIFY initiativeChanged)
    Q_PROPERTY(QList<int> armor READ armor NOTIFY armorChanged)
    Q_PROPERTY(int stamina READ stamina NOTIFY staminaChanged)
    Q_PROPERTY(QQmlListProperty<Weapon> weaponry READ weaponry  NOTIFY weaponryChanged)
    Q_PROPERTY(QStringList defenseList READ defenseList NOTIFY defensesChanged)
    Q_PROPERTY(int woundPenalty READ woundPenalty NOTIFY penaltyChanged)
    Q_PROPERTY(int health READ health NOTIFY healthChanged)
    Q_PROPERTY(QQmlListProperty<CombatAction> actions READ actions NOTIFY actionsChanged)
    Q_PROPERTY(QQmlListProperty<Combatant> targets READ targets NOTIFY targetsChanged)

public:
    explicit Combatant(QObject *parent = 0);
    Combatant(QString name, int dex, int str, int sta, int wit, QObject *parent = 0);
~Combatant();


    int attack(CombatConstants::Attack attackType, Weapon *selectedWeapon);
    void setHealth(QList <int> HLCounts);
    void setArmor(int soak, int hardness, int penalty);
    int joinBattle(bool initial = true);
    QList<int> armor();

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
    QQmlListProperty<Weapon> weaponry();
    QString name() const;
    QQmlListProperty<Combatant> targets();
    Combatant* targetAtIndex(int index);
    void setList(QList<Combatant*>*list);
    int listCount();

    int stamina() const;
    QStringList defenseList();
    int woundPenalty();
    bool isIncapacitated();
    bool isDead();
    int health();
    QQmlListProperty<CombatAction> actions();
    QString dicePoolString(int actionIndex, int actionList, CombatAction::Pool poolType, int weaponIndex);
    int dicePool(int actionIndex, int actionList, CombatAction::Pool poolType, int weaponIndex );

signals:
    void nameChanged();
    void initiativeChanged();
    void staminaChanged();
    void armorChanged();
    void weaponryChanged();
    void defensesChanged();
    void penaltyChanged();
    void healthChanged();
    void actionsChanged();
    void targetsChanged();


private:
    QString myName;
    int myInitiative;
    HealthTrack myHealth;
    int myStrength;
    int myDexterity;
    int myStamina;
    int myWits;
    QMap<QString,int> myAbilities;
    QList<Weapon *> myPanoply;
    int myArmorSoak;
    int myHardness;
    int myMobilityPenalty;
    int myOnslaught;
    int myCrashCounter;
    void initialize();
    int parryDefense(Weapon *weapon);
    int myCrashGuard;
    QList<Combatant*> *targetList;
    QList<Combatant*> temp;
    static QList<CombatAction *> masterActionList;
    static QList<CombatAction *> crashedActionList;

};

#endif // COMBATANT_H



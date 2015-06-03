#ifndef COMBATTRACKER_H
#define COMBATTRACKER_H

#include "combatant.h"
#include "combatconstants.h"
#include <QObject>
#include <QList>

class TraitRating:public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name MEMBER myName NOTIFY nameChanged)
    Q_PROPERTY(unsigned int stat MEMBER myRating NOTIFY ratingChanged)
public:
    explicit TraitRating(QObject *parent = 0);
    TraitRating(QString name, unsigned int rating = 0, QObject *parent = 0);
signals:
    void nameChanged();
    void ratingChanged();
private:
    QString  myName;
    unsigned int myRating;
};

Q_DECLARE_METATYPE(QList<TraitRating*>)
Q_DECLARE_METATYPE(QList<Combatant*>)
Q_DECLARE_METATYPE(QList<Weapon*>)
class CombatTracker : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Combatant> currentRound READ currentRound NOTIFY currentRoundChanged)
    Q_PROPERTY(QQmlListProperty<Combatant> nextRound READ nextRound NOTIFY nextRoundChanged)
    Q_PROPERTY(QQmlListProperty<TraitRating> newCombatantAttributes READ newCombatantAttributes NOTIFY attributesChanged)
    Q_PROPERTY(QQmlListProperty<TraitRating> newCombatantAbilities READ newCombatantAbilities NOTIFY abilitiesChanged)
    Q_PROPERTY(QStringList actions READ actions NOTIFY actionsChanged)
    Q_PROPERTY(QQmlListProperty<Combatant> targets READ validTargets NOTIFY targetsChanged)
    Q_PROPERTY(QQmlListProperty<Weapon> newCombatantWeapons READ newCombatantWeapons NOTIFY weaponsChanged)
public:
    explicit CombatTracker(QObject *parent = 0);
    ~CombatTracker();

    void addCombatant(Combatant *add);
    void attack(Combatant * attacker, int aWeapon, Combatant *defender, int dWeapon, CombatConstants::Attack attackType, CombatConstants::Defense defenseType = CombatConstants::Overall);
    QQmlListProperty<Combatant> currentRound();
    QQmlListProperty<Combatant> nextRound();
    QQmlListProperty<Combatant> validTargets();
    QQmlListProperty<TraitRating> newCombatantAttributes();
    QQmlListProperty<TraitRating> newCombatantAbilities();
    QQmlListProperty<Weapon> newCombatantWeapons();
    QStringList actions();

signals:
    void currentRoundChanged();
    void nextRoundChanged();
    void abilitiesChanged();
    void attributesChanged();
    void actionsChanged();
    void targetsChanged();
    void weaponsChanged();

public slots:
    void add(QString name, int soak, int hardness, int penalty);
    void addWeapon(QString name, int qual, int weight, QString ability, int damage, int range);
    void cleanDialog();

private:
    QList<Combatant *> myCurrentRound;
    QList<Combatant *> myNextRound;
    QList<TraitRating *> myDialogAbilities;
    QList<TraitRating *> myDialogAttributes;
    int currentTick;
    bool inBattle;
    void binaryInsertion(QList<Combatant *> *host, Combatant* add, int left, int right);
    QStringList myActionList;
    QList<Combatant *> myTargets;
    QList<Weapon *> myDialogWeapons;
};

#endif // COMBATTRACKER_H

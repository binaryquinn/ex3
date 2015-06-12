#ifndef COMBATTRACKER_H
#define COMBATTRACKER_H

#include "combatant.h"
#include "combatconstants.h"
#include <QObject>
#include <QList>



Q_DECLARE_METATYPE(QList<Combatant*>)
class CombatTracker : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Combatant> currentRound READ currentRound NOTIFY currentRoundChanged)
    Q_PROPERTY(QQmlListProperty<Combatant> nextRound READ nextRound NOTIFY nextRoundChanged)
    Q_PROPERTY(QStringList actions READ actions NOTIFY actionsChanged)
    Q_PROPERTY(QQmlListProperty<Combatant> targets READ validTargets NOTIFY targetsChanged)
    Q_PROPERTY(bool inBattle MEMBER battleStarted NOTIFY inBattleChanged)
public:
    explicit CombatTracker(QObject *parent = 0);
    ~CombatTracker();

    Q_INVOKABLE void attack(int attackerIndex, int aWeapon, int defenderIndex, int dWeapon, int attackType, int defenseType = CombatConstants::Overall);
    QQmlListProperty<Combatant> currentRound();
    QQmlListProperty<Combatant> nextRound();
    QQmlListProperty<Combatant> validTargets();
    QStringList actions();
    bool inBattle();

signals:
    void currentRoundChanged();
    void nextRoundChanged();
    void actionsChanged();
    void targetsChanged();
    void inBattleChanged();


public slots:
    void addCombatant(Combatant *add);

private:
    QList<Combatant *> myCurrentRound;
    QList<Combatant *> myNextRound;
    int currentTick;
    bool battleStarted;
    void binaryInsertion(QList<Combatant *> *host, Combatant* add, int left, int right);
    QStringList myActionList;
    QList<Combatant *> myTargets;
};

#endif // COMBATTRACKER_H

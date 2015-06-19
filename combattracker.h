#ifndef COMBATTRACKER_H
#define COMBATTRACKER_H

#include "combatant.h"
#include "combatconstants.h"
#include <QObject>
#include <QList>
#include <QMap>


Q_DECLARE_METATYPE(QList<Combatant*>)
class CombatTracker : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Combatant> currentRound READ currentRound NOTIFY currentRoundChanged)
    Q_PROPERTY(QQmlListProperty<Combatant> nextRound READ nextRound NOTIFY nextRoundChanged)
    Q_PROPERTY(QQmlListProperty<Combatant> targets READ validTargets NOTIFY targetsChanged)
    Q_PROPERTY(bool inBattle MEMBER battleStarted NOTIFY inBattleChanged)
    Q_PROPERTY(QList<int> currentTicks READ currentTicks NOTIFY currentTicksChanged)
    Q_PROPERTY(QList<int> nextTicks READ nextTicks NOTIFY nextTicksChanged)
public:
    explicit CombatTracker(QObject *parent = 0);
    ~CombatTracker();

    Q_INVOKABLE void attack(int attackerIndex, int aWeapon, int defenderIndex, int dWeapon, int attackType, int defenseType = CombatConstants::Overall);
    Q_INVOKABLE void modifyCombatant(int index, bool current, int unit, int amount, bool done);
    QQmlListProperty<Combatant> currentRound();
    QQmlListProperty<Combatant> nextRound();
    QQmlListProperty<Combatant> validTargets();
    bool inBattle();

    QList<int> currentTicks();
    Q_INVOKABLE QQmlListProperty<Combatant> combatantsOnTick(int tick, CombatConstants::Rounds which);
    QList<int> nextTicks();



signals:
    void currentRoundChanged();
    void nextRoundChanged();
    void targetsChanged();
    void inBattleChanged();
    void currentTicksChanged();
    void nextTicksChanged();


public slots:
    void addCombatant(Combatant *add);

private:
    QList<Combatant *> myCurrentRound;
    QList<Combatant *> myNextRound;
    int currentTick;
    bool battleStarted;
    void binaryInsertion(QList<Combatant *> *host, Combatant* add, int left, int right);
    QList<Combatant *> myTargets;
    bool targetHurt;
    QMap<int, Combatant *> currentRoundMap;
    QMap<int, Combatant *> nextRoundMap;
};

#endif // COMBATTRACKER_H

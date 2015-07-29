#ifndef COMBATTRACKER_H
#define COMBATTRACKER_H

#include "combatant.h"
#include "combatconstants.h"
#include <QObject>
#include <QList>
#include <QMap>


Q_DECLARE_METATYPE(QList<Combatant*>)
Q_DECLARE_METATYPE(QList<int>)
class CombatTracker : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Combatant> currentRound READ currentRound NOTIFY currentRoundChanged)
    Q_PROPERTY(QQmlListProperty<Combatant> nextRound READ nextRound NOTIFY nextRoundChanged)
     Q_PROPERTY(bool inBattle MEMBER battleStarted NOTIFY inBattleChanged)
    Q_PROPERTY(QVariantList currentTicks READ currentTicks NOTIFY currentTicksChanged)
    Q_PROPERTY(QVariantList nextTicks READ nextTicks NOTIFY nextTicksChanged)
public:
    explicit CombatTracker(QObject *parent = 0);
    ~CombatTracker();

    Q_INVOKABLE void attack(int attackerIndex, int aWeapon, int defenderIndex, int dWeapon, int attackType, int defenseType = CombatConstants::Overall);

    Q_INVOKABLE void modifyCombatants(int attacker, int attackUnit, int attackAmount, bool done, int defender, int defenderUnit, int defenderAmount);
    QQmlListProperty<Combatant> currentRound();
    QQmlListProperty<Combatant> nextRound();

    bool inBattle();

    QVariantList currentTicks();
    QVariantList nextTicks();



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
    int myCurrentTick;
    bool battleStarted;
    void binaryInsertion(QList<Combatant *> *host, Combatant* add, int left, int right);
    QList<Combatant *> myTargets;
    bool targetHurt;
    QMultiMap<int, Combatant *> currentRoundMap;
    QMultiMap<int, Combatant *> nextRoundMap;
    void modifyCombatant(Combatant* subject , int unit, int amount, bool done);

};

#endif // COMBATTRACKER_H

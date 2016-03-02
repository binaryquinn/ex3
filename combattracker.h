#ifndef COMBATTRACKER_H
#define COMBATTRACKER_H

#include "combatant.h"
#include "combatconstants.h"
#include <QObject>
#include <QList>
#include <QMap>
#include <QJsonObject>

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


    Q_INVOKABLE void modifyCombatants(QJsonObject tickActionsList);
    Q_INVOKABLE int dicePool(int actorIndex, int actionIndex, int actionList, int poolType, int weaponIndex);
    Q_INVOKABLE QString dicePoolString(int attackerIndex, int actionIndex, int actionList, int poolType, int weaponIndex);
    QQmlListProperty<Combatant> currentRound();
    QQmlListProperty<Combatant> nextRound();

    bool inBattle();

    QVariantList currentTicks();
    QVariantList nextTicks();



    Q_INVOKABLE int roll(int dice);

signals:
    void currentRoundChanged();
    void nextRoundChanged();
    void targetsChanged();
    void inBattleChanged();
    void currentTicksChanged();
    void nextTicksChanged();


public slots:
    void addCombatant(Combatant *add, bool iniGiven);

private:
    QList<Combatant *> myCurrentRound;
    QList<Combatant *> myNextRound;
    int myCurrentTick;
    bool battleStarted;
    QList<Combatant *> myTargets;
    QMultiMap<int, Combatant *> currentRoundMap;
    QMultiMap<int, Combatant *> nextRoundMap;

    void binaryInsertion(QList<Combatant *> *host, Combatant* add, int left, int right);
    void modifyCombatant(Combatant *subject, QMap<QString, int> deltaMap);
    void updateActionDeltas(QJsonObject actionJson, QMap<QString, int> &actionMap);
};

#endif // COMBATTRACKER_H

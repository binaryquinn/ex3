#ifndef COMBATTRACKER_H
#define COMBATTRACKER_H

#include "combatant.h"

#include <QObject>
#include <QList>

Q_DECLARE_METATYPE(QList<Combatant*>)
class CombatTracker : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Combatant> currentRound READ currentRound NOTIFY currentRoundChanged)
    Q_PROPERTY(QQmlListProperty<Combatant> nextRound READ nextRound NOTIFY nextRoundChanged)
public:
    explicit CombatTracker(QObject *parent = 0);
    ~CombatTracker();

    void addCombatant(Combatant *add);
    void attack(Combatant * attacker, int aWeapon, Combatant *defender, int dWeapon, CombatConstants::Attack attackType, CombatConstants::Defense defenseType = CombatConstants::Overall);
    QQmlListProperty<Combatant> currentRound();
    QQmlListProperty<Combatant> nextRound();

    friend bool operator <( Combatant &lhs, Combatant &rhs) ;
signals:
    void currentRoundChanged();
    void nextRoundChanged();

public slots:
    void add(QString name, int dex, int str,int sta, int wit);

private:
    QList<Combatant *> myCurrentRound;
    QList<Combatant *> myNextRound;
    int currentTick;
    bool inBattle;
    void binaryInsertion(QList<Combatant *> *host, Combatant* add, int left, int right);
};

#endif // COMBATTRACKER_H

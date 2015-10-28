#ifndef HEALTHTRACK_H
#define HEALTHTRACK_H


#include "combatconstants.h"

class HealthTrack : public QObject
{
    Q_OBJECT
public:
    HealthTrack(QObject *parent = 0);
    ~HealthTrack();
    int currentPenalty();
    void takeDamage(int amount, CombatConstants::Wounds type);
    bool isDead();
    bool isIncapacitated();
    void setHealthLevel(int level, int number);
    int healthLeft();
signals:
    void healthChanged();
    void penaltyChanged();

private:
    QList<CombatConstants::Wounds> myHealth;
    QList<QPair<int,int> > myLevels;
    int myWoundPenalty;
    int bashingCount;
    int lethalCount;
    int aggravatedCount;
    bool countRollOver;
};

#endif // HEALTHTRACK_H

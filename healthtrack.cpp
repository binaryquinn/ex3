#include "healthtrack.h"

HealthTrack::HealthTrack(QObject *parent):QObject(parent)
{

    for(int loop = 0; loop < 7;loop++)
        myHealth << CombatConstants::None;

    myLevels << QPair<int,int>(0,1) << QPair<int,int>(-1,2) << QPair<int,int>(-2,2) << QPair<int,int>(-4,1) << QPair<int,int>(INT_MIN,1);
    bashingCount = lethalCount = aggravatedCount = myWoundPenalty = 0;
    countRollOver = true;
    myWoundPenalty = 0;
}

HealthTrack::~HealthTrack()
{

}


int HealthTrack::currentPenalty()
{
    return myWoundPenalty;
}

void HealthTrack::takeDamage(int amount, CombatConstants::Wounds type)
{
    if(amount > 0)
    {
        int rollOver = 0;
        int start = 0;
        switch(type)
        {
            case CombatConstants::Aggravated :
            {
                aggravatedCount += amount;
                start = 0;
                break;
            };
            case CombatConstants::Lethal :
            {
                lethalCount += amount;
                start = aggravatedCount;
                break;
            };
            case CombatConstants::Bashing :
            {
                bashingCount += amount;
                start = aggravatedCount + lethalCount;
                break;
            };
            default: return;
        };
        if(start < myHealth.count())
        {
            for(int counter = 0;counter < amount; counter++)
            {
                myHealth.insert(start,type);
                if(myHealth.last() == CombatConstants::Bashing)
                    rollOver++;
                myHealth.pop_back();
            }
            if(countRollOver)
            {
                if(rollOver > 0)
                {
                    countRollOver = false;
                    takeDamage(rollOver, CombatConstants::Lethal);
                    countRollOver = true;
                }
                emit healthChanged();
                int wounds = aggravatedCount + lethalCount + bashingCount;
                int loop = 0;
                int oldPenalty = myWoundPenalty;
                for(;loop < myLevels.count() && wounds > 0;loop++)
                    wounds -= myLevels[loop].second;
                myWoundPenalty = (loop > myLevels.count())? myLevels.last().first : myLevels[loop-1].first;
                if(oldPenalty != myWoundPenalty)
                    emit penaltyChanged();
            }
        }
    }
}

bool HealthTrack::isDead()
{
    return (myHealth.last() > CombatConstants::Bashing);
}

bool HealthTrack::isIncapacitated()
{
    return (myHealth.last() == CombatConstants::Bashing);
}

void HealthTrack::setHealthLevel(int level, int number)
{
    if(level > -1 && level < myLevels.count())
    {
        int difference = myLevels[level].second - number;
        if(difference != 0)
        {
            if(difference < 0)
            {
                for(; difference < 0; difference++)
                    myHealth.append(CombatConstants::None);
            }
            else
            {
                for(; difference > 0; difference--)
                    myHealth.pop_back();
            }
            emit healthChanged();
        }
    }
}

int HealthTrack::healthLeft()
{
    return myHealth.size() - (aggravatedCount + lethalCount + bashingCount);
}

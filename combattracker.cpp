#include "combattracker.h"
#include "d10.h"
#include <QDebug>
#include "combatant.h"

CombatTracker::CombatTracker(QObject *parent) : QObject(parent)
{
    battleStarted = false;
    myCurrentTick = 0;

}

CombatTracker::~CombatTracker()
{
    qDeleteAll(myTargets);
}

void CombatTracker::addCombatant(Combatant *add, bool iniGiven)
{
    add->setParent(this);
    if(!iniGiven)
        add->joinBattle();

    QMultiMap<int, Combatant * > *hostMap;
    if(!battleStarted)
    {
        hostMap = &currentRoundMap;
    }
    else
    {
        hostMap = &nextRoundMap;
    }


    hostMap->insertMulti(add->initiative(),add);

    myTargets.append(add);
    emit targetsChanged();
    add->setList(&myTargets);
    connect(this, SIGNAL(targetsChanged()),add,SIGNAL(targetsChanged()));

    if(!battleStarted){
        if(myCurrentTick < add->initiative())
            myCurrentTick = add->initiative();
        emit currentTicksChanged();
        emit currentRoundChanged();
    }
    else
    {
        emit  nextTicksChanged();
        emit nextRoundChanged();
    }
}

int CombatTracker::roll(int dice)
{
    return D10::roll(dice);
}


void CombatTracker::modifyCombatant(Combatant *subject, QMap<QString, int> deltaMap)
{
    QMultiMap<int, Combatant* >* hostMap = currentRoundMap.contains(subject->initiative(),subject)? &currentRoundMap : &nextRoundMap;
    int tick = subject->initiative();

    if(deltaMap["i"] != 0)
        subject->changeInitiative(deltaMap["i"]);
    if(deltaMap["h"] != 0)
        subject->suffer(std::abs(deltaMap["h"]),(CombatConstants::Wounds)deltaMap["w"]);

    hostMap->remove(tick,subject);
    if(deltaMap.contains("d"))
    {
        hostMap =  &nextRoundMap;
    }

    if(!(subject->isDead()||subject->isIncapacitated()))
        hostMap->insertMulti(subject->initiative(), subject);
    else
        myTargets.removeOne(subject);
}

void CombatTracker::updateActionDeltas(QJsonObject actionJson, QMap<QString,int> &actionMap)
{
    int aInitDelta, aDamage, aUnit;

    aInitDelta = actionJson["i"].toInt();
    aDamage = actionJson["h"].toInt();
    aUnit = actionJson["w"].toInt();
    if(!actionMap.isEmpty())
    {
        actionMap.insert("i", aInitDelta);
        actionMap.insert("h", aDamage);
        actionMap.insert("w", aUnit);
    }
    else
    {
        actionMap["i"] += aInitDelta;
        actionMap["h"] += aDamage;
        actionMap["w"] += aUnit;
    }

    if(actionJson.contains("d"))
        actionMap.insert("d", actionJson["d"].toBool());

}


void CombatTracker::modifyCombatants(QJsonObject tickActionsList)
{
    QMap<Combatant* , QMap<QString, int> > tickActorsMap;

    int dIndex;
    QJsonObject attackerJSON, defenderJSON;
    Combatant* attacker, * defender;
    foreach (QString indexKey, tickActionsList.keys())
    {
        attackerJSON = tickActionsList[indexKey].toObject()["attacker"].toObject();
        attacker = myCurrentRound[attackerJSON["n"].toInt()];

        if(!tickActorsMap.contains(attacker))
        {
            tickActorsMap.insert(attacker,  QMap<QString, int>());
        }
        updateActionDeltas(attackerJSON, tickActorsMap[attacker]);

        defenderJSON = tickActionsList[indexKey].toObject()["defender"].toObject();
        if(!defenderJSON.isEmpty())
        {
            dIndex = defenderJSON["n"].toInt();
            defender = (dIndex < myTargets.indexOf(attacker))? myTargets[dIndex] : myTargets[dIndex+1];

            if(!tickActorsMap.contains(defender))
            {
                tickActorsMap.insert(defender, QMap<QString, int>());
            }
            updateActionDeltas(defenderJSON, tickActorsMap[defender]);
        }
    }

    foreach(Combatant* actor, tickActorsMap.keys())
    {
        modifyCombatant(actor, tickActorsMap[actor]);
        if(actor->isDead()||actor->isIncapacitated())
            actor->deleteLater();
    }

    if(currentRoundMap.values(myCurrentTick).count() < 1)
    {
        myCurrentRound.clear();
        if(currentRoundMap.count() < 1)
        {
            currentRoundMap.swap(nextRoundMap);
            myNextRound.clear();
        }
        myCurrentTick = currentTicks()[0].toInt();
        foreach(Combatant* combat,currentRoundMap.values(myCurrentTick))
        {
            combat->refreshTurn();
            emit combat->targetsChanged();
        }
    }

    if(myTargets.length() < 2)
    {
        battleStarted = false;
        emit inBattleChanged();
    }

    emit targetsChanged();
    emit currentTicksChanged();
    emit currentRoundChanged();
    emit nextTicksChanged();
    emit nextRoundChanged();

}

int CombatTracker::dicePool(int actorIndex, int actionIndex, int actionList, int poolType, int weaponIndex)
{
    if(actorIndex < 0 || actionIndex < 0)
        return 0;
    Combatant* actor =  myCurrentRound[actorIndex];

    return actor->dicePool(actionIndex, actionList, (CombatAction::Pool)poolType, weaponIndex);
}

QString CombatTracker::dicePoolString(int attackerIndex, int actionIndex, int actionList, int poolType, int weaponIndex)
{
    if(attackerIndex < 0 || actionIndex < 0)
        return "";
    Combatant* attacker = myCurrentRound[attackerIndex];
    return attacker->dicePoolString(actionIndex, actionList, (CombatAction::Pool)poolType, weaponIndex);
}

QQmlListProperty<Combatant> CombatTracker::currentRound()
{
    if(currentRoundMap.count() > 0  && myCurrentRound != currentRoundMap.values(myCurrentTick))
    {
        myCurrentRound = currentRoundMap.values(myCurrentTick);
    }
    return QQmlListProperty<Combatant>(this,myCurrentRound);
}

QQmlListProperty<Combatant> CombatTracker::nextRound()
{

    if(nextRoundMap.count() > 0  && myNextRound != nextRoundMap.values())
    {
        myNextRound = nextRoundMap.values();
    }
    return QQmlListProperty<Combatant>(this, myNextRound);
}



QVariantList CombatTracker::currentTicks()
{
    QVariantList temp;
    foreach(int num,currentRoundMap.uniqueKeys())
    {
        int index ;
        for( index = 0; index < temp.size() && num < temp[index].toInt();index++);
        temp.insert(index, QVariant(num));
    }
    return temp;
}


QVariantList CombatTracker::nextTicks()
{
    QVariantList temp;
    foreach(int num,nextRoundMap.uniqueKeys())
    {
        int index ;
        for( index = 0; index < temp.size() && num < temp[index].toInt();index++);
        temp.insert(index, QVariant(num));
    }
    return temp;
}

bool CombatTracker::inBattle()
{
    return battleStarted;
}

void CombatTracker::binaryInsertion(QList<Combatant *> *host, Combatant* add, int left, int right)
{
    int mid = (left+right)/2;
    if (right <= left )
    {
        if( mid + 1 < host->count() && add->initiative() < host->at(mid)->initiative())
            host->insert(mid+1,add);
        else
            host->insert(mid,add);
    }
    else
    {
        if (add->initiative() < host->at(mid)->initiative())
            binaryInsertion(host, add, ++mid, right);
        else
            binaryInsertion(host, add, left, --mid);
    }
}

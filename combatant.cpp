#include "combatant.h"
#include "combataction.h"
#include <math.h>
#include <QDebug>
#include <QFile>
#include <QXmlStreamReader>
#include "d10.h"


QList<CombatAction *> Combatant::masterActionList;
QList<CombatAction *> Combatant::crashedActionList;
Combatant::Combatant(QObject *parent):QObject(parent), myName(""), myStrength(0), myDexterity(0), myStamina(0), myWits(0), myArmorSoak(0),myHardness(0)
{
    initialize();
}

Combatant::Combatant(QString name, int str, int dex, int sta, int wit, QObject *parent):
    QObject(parent), myName(name), myStrength(str), myDexterity(dex), myStamina(sta), myWits(wit), myArmorSoak(0), myHardness(0)
{
    initialize();
}

Combatant::~Combatant()
{
    qDeleteAll(myPanoply);
}

void Combatant::setHealth(QList<int> HLCounts)
{
    if(HLCounts.size() != 5)
        return;

    for(int hLevel = 0; hLevel < HLCounts.size(); hLevel++)
        myHealth.setHealthLevel(hLevel, HLCounts[hLevel]);
}

void Combatant::setArmor(int soak, int hardness, int penalty)
{
    myArmorSoak = soak;
    myHardness = hardness;
    myMobilityPenalty = penalty;
}

int Combatant::joinBattle(bool initial)
{
    myInitiative = D10::roll(std::max(myWits + myAbilities["Awareness"],0));
    myInitiative+= (initial)? 3 : 0;
    return myInitiative;
}

QList<int> Combatant::armor()
{
    QList<int> myArmor;
    myArmor << myArmorSoak << myHardness << myMobilityPenalty;
    return myArmor;
}

int Combatant::attack(CombatConstants::Attack attackType, Weapon * selectedWeapon)
{
    int attackBase = myDexterity + myAbilities[selectedWeapon->ability()] + myHealth.currentPenalty();
    if(attackType == CombatConstants::Withering)
        attackBase += selectedWeapon->accuracy();
    return attackBase;
}


int Combatant::damage(CombatConstants::Attack attackType, Weapon *selectedWeapon)
{
    if(attackType == CombatConstants::Withering)
        return myStrength + selectedWeapon->damage();
    return myInitiative;
}

int Combatant::defense(CombatConstants::Defense defenseType, Weapon *weapon, bool onslaught)
{
    int value;
    int parryDef =  parryDefense(weapon);
    int evasion = ceil((double)(myDexterity+myAbilities["Dodge"])/2) - myMobilityPenalty;;
    switch(defenseType)
    {
        case CombatConstants::Overall: value = (evasion > parryDef) ? evasion : parryDef; break;
        case CombatConstants::Evasion: value = evasion; break;
        default: value = parryDef; break;
    };
    value += myHealth.currentPenalty();
    value -= myOnslaught;
    if(onslaught)
        myOnslaught++;
    value = std::max(value,0);
    return value;
}

void Combatant::refreshTurn()
{
    myOnslaught = 0;
    if(myCrashGuard > 0)
        myCrashGuard--;
    if(myCrashCounter == 3)
    {
        resetInitiative();
        myCrashGuard = 2;
    }
    if(myInitiative < 1)
        myCrashCounter++;
    else
        myCrashCounter = 0;
}

void Combatant::resetInitiative()
{
    myInitiative = 3;
    myCrashCounter = 0;
    emit initiativeChanged();
}

void Combatant::changeInitiative(int value)
{
    if(value != 0)
    {
        int guardCheck = myInitiative;
        myInitiative += value;
        emit initiativeChanged();
        if(guardCheck < 1 && myInitiative > 0)
            myCrashGuard = 2;
    }
}

int Combatant::initiative()
{
    return myInitiative;
}

void Combatant::suffer(int amount, CombatConstants::Wounds damageType)
{
    myHealth.takeDamage(amount, damageType);
}


int Combatant::takeDamage(CombatConstants::Attack attackType, int damage, int overwhelming, CombatConstants::Wounds damageType)
{


    if(attackType == CombatConstants::Withering)
    {
        int postSoak = damage - (myStamina + myArmorSoak); //calculating dice pool
        if(postSoak < overwhelming)
            postSoak = overwhelming;
        postSoak = D10::roll(postSoak); //dice pool becomes dice successes
        int crashCheck = myInitiative;
        myInitiative -= postSoak;
        emit initiativeChanged();
        if(crashCheck > 0 && myInitiative < 1 && myCrashGuard < 1)
            postSoak+=5;
        return postSoak;
    }
    else
    {
        if( myInitiative < 1 || myHardness < damage)
        {
            int wounds = D10::roll(damage,false);
            myHealth.takeDamage(wounds, damageType);
            return wounds;
        }
    }
    return 0;
}

void Combatant::setAbility(QString name, int value)
{
    if(myAbilities.contains(name))
        myAbilities[name] = value;
}




Weapon *Combatant::weapon(int selected)
{
    return myPanoply[selected];
}

void Combatant::addWeapon(Weapon *addition)
{
    addition->setParent(this);
    myPanoply.append(addition);
}

QQmlListProperty<Weapon> Combatant::weaponry()
{
    return QQmlListProperty<Weapon>(this, myPanoply);
}

QString Combatant::name() const
{
    return myName;
}

QQmlListProperty<Combatant> Combatant::targets()
{
    temp.clear();
    temp.append(*targetList);

    temp.removeOne(this);
    return QQmlListProperty<Combatant>(this, temp);
}

Combatant *Combatant::targetAtIndex(int index)
{
    return targetList->at(index);
}

void Combatant::setList(QList<Combatant *> *list)
{
    targetList = list;
}



int Combatant::stamina() const
{
    return myStamina;
}

QStringList Combatant::defenseList()
{
    QStringList defList;
    defList << QString("Evade: %1 Defense ").arg(defense(CombatConstants::Evasion,myPanoply[0],false));

    foreach(Weapon* weaponCheck, myPanoply)
    {
        defList << QString::fromLatin1("Parry with %1: %2 Defense").arg(weaponCheck->name()).arg(defense(CombatConstants::Parry,weaponCheck, false));
    }
    return defList;
}


void Combatant::initialize()
{

    myInitiative = myOnslaught = myCrashCounter = myCrashGuard = 0;
    QStringList abilist = CombatConstants::allAbilities();
    foreach(QString ability , abilist)
        myAbilities.insert(ability,0);

    if(masterActionList.empty())
    {
        QFile loadFile(QStringLiteral(":/defaults/actions.xml"));

        if (!loadFile.open(QIODevice::ReadOnly))
        {
            qWarning("Couldn't open actions file.");
        }

        QByteArray loadData = loadFile.readAll();
        QXmlStreamReader actionReader(loadData);

        QString name;
        bool flurry;
        bool rolled;
        bool crash;
        bool weapon;
        bool decisive;
        QVariant difficulty;
        CombatConstants::Targetting target;

        while(!actionReader.atEnd())
        {
            actionReader.readNext();
            if(actionReader.isStartElement())
            {
                if(actionReader.name() == "Action")
                {
                    name = actionReader.attributes().value("name").toString();
                    flurry = actionReader.attributes().value("flurry").toInt();
                    rolled = actionReader.attributes().value("rolled").toInt();
                    crash = actionReader.attributes().value("crashed").toInt();
                    weapon = actionReader.attributes().value("weapon").toInt();
                    target = (CombatConstants::Targetting)actionReader.attributes().value("target").toInt();
                    decisive = actionReader.attributes().hasAttribute("decisive")? actionReader.attributes().value("decisive").toInt(): false;
                    difficulty = actionReader.attributes().hasAttribute("difficulty")? actionReader.attributes().value("difficulty").toString():QVariant();
                    masterActionList.append( new CombatAction(name,flurry, rolled, crash, weapon, decisive, target, difficulty, this)) ;
                    if(crash)
                        crashedActionList.append(masterActionList.last());
                }
                if(actionReader.name() == "Pool")
                {
                    masterActionList.last()->addPool(actionReader.attributes().value("attribute").toString(), actionReader.attributes().value("ability").toString());
                }
            }
            loadFile.close();
        }
    }
    connect(&myHealth,&HealthTrack::penaltyChanged, this, &Combatant::penaltyChanged);
    connect(&myHealth,&HealthTrack::healthChanged, this, &Combatant::healthChanged);
}

int Combatant::parryDefense(Weapon *weapon)
{
    int ability = myAbilities.contains(weapon->ability()) ? myAbilities[weapon->ability()] : 0;
    return ceil((double)(myDexterity + ability)/2) + weapon->defense();
}

int Combatant::woundPenalty()
{
    return myHealth.currentPenalty();
}

bool Combatant::isIncapacitated()
{
    return myHealth.isIncapacitated();
}

bool Combatant::isDead()
{
    return myHealth.isDead();
}

int Combatant::health()
{
    return myHealth.healthLeft();
}

QQmlListProperty<CombatAction> Combatant::actions()
{

    if(myInitiative > 0 )
        return QQmlListProperty<CombatAction>(this, masterActionList);

    else
        return QQmlListProperty<CombatAction>(this, crashedActionList);

}

int Combatant::dicePool(int actionIndex, int actionList, CombatAction::Pool poolType, int weaponIndex)
{
    CombatAction * myAction = (actionList )? masterActionList.at(actionIndex) : crashedActionList.at(actionIndex);
    QPair<QString,QString> actionPool = myAction->getPool(poolType);
    if(actionPool == QPair<QString,QString>())
        return 0;
    int pool = (actionPool.first == "dexterity")?
                myDexterity : (actionPool.first == "strength")?
                    myStrength : (actionPool.first == "stamina")? myStamina: myWits;

    if(actionPool.second != "weapon")
        pool += myAbilities[actionPool.second];

    else if(myAction->isWeaponUsed() && weaponIndex > -1)
    {
        pool += myAbilities[myPanoply[weaponIndex]->ability()];
        if(!myAction->decisiveAction())
            pool += myPanoply[weaponIndex]->accuracy();
    }
    return pool;
}

QString Combatant::dicePoolString(int actionIndex, int actionList, CombatAction::Pool poolType, int weaponIndex)
{
    CombatAction * myAction = (actionList)? masterActionList.at(actionIndex) : crashedActionList.at(actionIndex);
    QPair<QString,QString> actionPool = myAction->getPool(poolType);
    if(actionPool == QPair<QString,QString>())
        return "";
    QString poolString = QString("%1 + %2").arg(actionPool.first);
    if(actionPool.second != "weapon")
        poolString = poolString.arg(actionPool.second);
    else if(myAction->isWeaponUsed() && weaponIndex > -1)
    {        poolString = poolString.arg(myPanoply[weaponIndex]->ability());
        if(!myAction->decisiveAction())
            poolString.append(" + weapon accuracy");
    }
    return poolString;

}


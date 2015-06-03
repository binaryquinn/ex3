#include "weapon.h"
#include <QFile>
#include <QXmlStreamReader>
#include<QMap>
#include <QDebug>

QMap<Weapon::Quality , QMap< Weapon::WeightClass, QMap<Weapon::WeaponTrait, int> > > Weapon::stats;
QStringList Weapon::myWeaponTraits;
QMap<Weapon::Quality , QMap<QString, QMap<CombatConstants::Range, int> > > Weapon::rangeBands;
QStringList Weapon::myQualities;
QStringList Weapon::myWeightClases;

Weapon::Weapon(QObject *parent):QObject(parent), myQuality(Weapon::Mundane), myWeight(Weapon::Light), myAbility(""),  myWoundType(CombatConstants::Bashing), myRange(CombatConstants::Close), myStrength(false), myHanded(false)
{
    if(stats.empty())
        initialize();
}

Weapon::Weapon(QString name, Weapon::Quality qual, Weapon::WeightClass weight, QString abi, CombatConstants::Wounds type, CombatConstants::Range band, bool useStr, bool handed, QObject *parent):
    QObject(parent), myName(name),  myQuality(qual), myWeight(weight), myAbility(abi),myWoundType(type), myRange(band),  myStrength(useStr), myHanded(handed)
{
    if(stats.empty())
        initialize();
}


int Weapon::accuracy(CombatConstants::Range band) const
{
    if((myAbility != "Archery") && (myAbility!="Thrown"))
        return stats[myQuality][myWeight][Weapon::Accuracy];
    else if(band <= myRange)
        return rangeBands[myQuality][myAbility][band];
    else return INT_MIN;
}

int Weapon::damage() const
{
    return stats[myQuality][myWeight][Weapon::Damage];
}


int Weapon::defense() const
{
    if((myAbility != "Archery") && (myAbility!="Thrown"))
        return stats[myQuality][myWeight][Weapon::Accuracy];
    else return INT_MIN;
}

QString Weapon::ability() const
{
    return myAbility;
}

void Weapon::setAbility(const QString &value)
{
    myAbility = value;
}
bool Weapon::usesStrength() const
{
    return myStrength;
}

void Weapon::setUsesStrength(bool value)
{
    myStrength = value;
}
CombatConstants::Wounds Weapon::woundType() const
{
    return myWoundType;
}

void Weapon::setWoundType(CombatConstants::Wounds value)
{
    myWoundType = value;
}

int Weapon::overwhelming() const
{
    return stats[myQuality][myWeight][Weapon::Overwhelming];
}

QString Weapon::name() const
{
    return myName;
}

void Weapon::setName(const QString &value)
{
    myName = value;
}

bool Weapon::is2Handed() const
{
    return myHanded;
}

void Weapon::set2Handed(bool value)
{
    myHanded = value;
}

QStringList Weapon::qualities()
{
    if(myQualities.empty())
    {
        myQualities << "Mundane" << "Artifact";

    }
    return myQualities;
}

QStringList Weapon::weightClasses()
{
    if(myWeightClases.empty())
    {
        myWeightClases << "Light" << "Medium" << "Heavy";
    }
    return myWeightClases;
}

QStringList Weapon::weaponTraits()
{
    if(myWeaponTraits.empty())
    {
        myWeaponTraits << "Damage" << "Overwhelming" << "Accuracy" << "Defense";
    }
     return myWeaponTraits;
}

void Weapon::initialize()
{
    weaponTraits();

    QFile loadFile(QStringLiteral(":/defaults/weapons.xml"));

    if (!loadFile.open(QIODevice::ReadOnly))
    {
        qWarning("Couldn't open weapons file.");
    }

    QByteArray loadData = loadFile.readAll();
    QXmlStreamReader weaponReader(loadData);
    weaponReader.readNext();

    Weapon::Quality qualIndex = Weapon::Mundane;
    Weapon::WeightClass weightIndex = Weapon::Light;
    Weapon::WeaponTrait traitIndex = Weapon::Damage;

    while(!weaponReader.atEnd())
    {
        weaponReader.readNext();
        if(weaponReader.attributes().size()>0)
        {

            for(int attrCount = 0; attrCount < myWeaponTraits.size(); attrCount++)
            {
                stats[qualIndex][weightIndex][traitIndex]= weaponReader.attributes().value(myWeaponTraits[attrCount]).toInt();
                traitIndex = (traitIndex == Weapon::Damage)? Weapon::Overwhelming : ((traitIndex == Weapon::Overwhelming)?
                                                                                         Weapon::Accuracy : ((traitIndex == Weapon::Accuracy)? Weapon::Defense : Weapon::Damage));
            }
            weightIndex = (weightIndex == Weapon::Light)? Weapon::Medium : ((weightIndex == Weapon::Medium)? Weapon::Heavy : Weapon::Light);
        }
        else if(weaponReader.isStartElement() && weaponReader.name() == "Artifact")
        {
            qualIndex = Weapon::Artifact;
        }
    }
    loadFile.close();

    qualIndex = Weapon::Mundane;
    QString ability = "Thrown";
    CombatConstants::Range rangeIndex = CombatConstants::Close;
    QStringList rangeList = CombatConstants::ranges();

    loadFile.setFileName(":/defaults/ranges.xml");
    if (!loadFile.open(QIODevice::ReadOnly))
    {
        qWarning("Couldn't open weapons file.");
    }

    loadData = loadFile.readAll();
    weaponReader.addData(loadData);
    weaponReader.readNext();

    while(!weaponReader.atEnd())
    {
        weaponReader.readNext();
        if(weaponReader.attributes().size() > 0)
        {

            for(int attrCount = 0; attrCount < rangeList.size(); attrCount++)
            {
                rangeBands[qualIndex][ability][rangeIndex] = weaponReader.attributes().value(rangeList[attrCount]).toInt();
                rangeIndex= (rangeIndex == CombatConstants::Close)?
                            CombatConstants::Short : ((rangeIndex == CombatConstants::Short)?
                                                          CombatConstants::Medium : ((rangeIndex == CombatConstants::Medium )?
                                                                                         CombatConstants::Long : ((rangeIndex == CombatConstants::Long )?
                                                                                                                      CombatConstants::Extreme : CombatConstants::Close)));
            }
            ability = "Archery";
        }
        else if(weaponReader.isStartElement()&& weaponReader.name() == "Artifact")
        {
            qualIndex = Weapon::Artifact;
            ability = "Thrown";
        }
    }
}
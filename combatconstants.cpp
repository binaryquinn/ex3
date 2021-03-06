#include "combatconstants.h"
#include <QFile>
#include <QXmlStreamReader>

QStringList CombatConstants::myAttackAbilities;
QStringList CombatConstants::myOtherAbilities;
QStringList CombatConstants::myRanges;
QStringList CombatConstants::myDamageTypes;
QStringList CombatConstants::myAttributes;
QStringList CombatConstants::myUnits;
QStringList CombatConstants::myVerbs;
QStringList CombatConstants::myActions;

QStringList CombatConstants::combatAbilities()
{

    if(myAttackAbilities.empty())
    {
        myAttackAbilities << "Archery" << "Brawl" << "Martial Arts" << "Melee"<< "Thrown";
    }
    return myAttackAbilities;
}

QStringList CombatConstants::allAbilities()
{
    if(myOtherAbilities.empty())
        myOtherAbilities << "Athletics" << "Awareness" << "Dodge"  << "Resistance" << "Ride" ;
    QStringList bothLists;
    bothLists << myOtherAbilities << combatAbilities();
    bothLists.sort();

    return bothLists;
}

QStringList CombatConstants::ranges()
{
    if(myRanges.empty())
    {
        myRanges<< "Close" << "Short" << "Medium" << "Long"<< "Extreme";
    }
    return myRanges;
}

QStringList CombatConstants::damageTypes()
{
    if(myDamageTypes.empty())
    {
        myDamageTypes<< "Bashing" << "Lethal" << "Aggravated";
    }
    return myDamageTypes;
}

QStringList CombatConstants::attributes()
{
    if(myAttributes.empty())
    {
        myAttributes << "Strength" << "Dexterity" << "Stamina" << "Wits";
    }
    return myAttributes;
}

QStringList CombatConstants::units()
{
    if(myUnits.empty())
    {
        myUnits << "Initiative" << damageTypes();
    }
    return myUnits;
}

QStringList CombatConstants::verbs()
{
    if(myVerbs.empty())
    {
        myVerbs << "Gains" << "Loses";
    }
    return myVerbs;
}

QStringList CombatConstants::actions()
{
    if(myActions.empty())
    {
        QFile loadFile(QStringLiteral(":/defaults/actions.xml"));

        if (!loadFile.open(QIODevice::ReadOnly))
        {
            qWarning("Couldn't open actions file.");
        }

        QByteArray loadData = loadFile.readAll();
        QXmlStreamReader actionReader(loadData);

        while(!actionReader.atEnd())
        {
            actionReader.readNext();
            if(actionReader.isStartElement() && actionReader.name() == "Action")
            {
                myActions << actionReader.attributes().value("name").toString();
            }
        }
        loadFile.close();
    }
    return myActions;
}

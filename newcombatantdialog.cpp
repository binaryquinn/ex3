#include "newcombatantdialog.h"
#include "combatconstants.h"
#include <QDebug>

NewCombatantDialog::NewCombatantDialog(QObject *parent) : QObject(parent)
{
    foreach(QString ability,CombatConstants::allAbilities())
        myAbilities.append(new TraitRating(ability,0));

    foreach(QString attributes,CombatConstants::attributes())
        myAttributes.append(new TraitRating(attributes,1));

        myHLs.append(new TraitRating("0", 1));
        myHLs.append(new TraitRating("-1", 2));
        myHLs.append(new TraitRating("-2", 2));
        myHLs.append(new TraitRating("-4", 1));
        myHLs.append(new TraitRating("Incapacitated", 1));

    myWeapons.append(new Weapon("Unarmed", Weapon::Mundane, Weapon::Light,"Brawl"));
}

QQmlListProperty<TraitRating> NewCombatantDialog::attributes()
{
    return QQmlListProperty<TraitRating>(this,myAttributes);
}

QQmlListProperty<TraitRating> NewCombatantDialog::abilities()
{
    return QQmlListProperty<TraitRating>(this,myAbilities);
}

QQmlListProperty<Weapon> NewCombatantDialog::weapons()
{
    return QQmlListProperty<Weapon>(this, myWeapons);
}

QQmlListProperty<TraitRating> NewCombatantDialog::healthLevels()
{
    return QQmlListProperty<TraitRating>(this,myHLs);
}


void NewCombatantDialog::cleanDialog()
{
    int cleaner = 0;

    for(;cleaner < myAttributes.count();cleaner++)
        myAttributes[cleaner]->setProperty("stat",1);

    for(cleaner = 0;cleaner < myAbilities.count();cleaner++)
        myAbilities[cleaner]->setProperty("stat",0);

    myHLs[0]->setProperty("stat",1);
    myHLs[1]->setProperty("stat",2);
    myHLs[2]->setProperty("stat",2);
    myHLs[3]->setProperty("stat",1);
    myHLs[4]->setProperty("stat",1);

    myWeapons.clear();
    myWeapons.append(new Weapon("Unarmed",Weapon::Mundane, Weapon::Light,"Brawl"));

    emit attributesChanged();
    emit abilitiesChanged();
    emit healthLevelsChanged();
    emit weaponsChanged();
}

void NewCombatantDialog::makeCombatant(QString name, int soak, int hardness, int penalty)
{
    int str = myAttributes[0]->property("stat").toInt();
    int dex = myAttributes[1]->property("stat").toInt();
    int sta = myAttributes[2]->property("stat").toInt();
    int wit = myAttributes[3]->property("stat").toInt();
    Combatant * newbie = new Combatant(name,dex,str,sta,wit);
    newbie->setArmor(soak,hardness,penalty);

    foreach (TraitRating* trait, myAbilities)
        newbie->setAbility(trait->property("name").toString(),trait->property("stat").toInt());

    QList<int> hlNums;
    foreach(TraitRating *hl, myHLs)
        hlNums.append(hl->property("stat").toInt());
    newbie->setHealth(hlNums);

    foreach (Weapon * wep, myWeapons)
        newbie->addWeapon(wep);

    emit combatantMade(newbie);
}

void NewCombatantDialog::addWeapon(QString name, int qual, int weight, QString ability, int damage, int range)
{
    myWeapons.append(new Weapon(name,(Weapon::Quality)qual,(Weapon::WeightClass)weight, ability, (CombatConstants::Wounds)damage, (CombatConstants::Range)range));
    emit weaponsChanged();

}

TraitRating::TraitRating(QObject *parent):QObject(parent), myName(""), myRating(0)
{

}

TraitRating::TraitRating(QString name, unsigned int rating, QObject *parent):QObject(parent), myName(name), myRating(rating)
{

}

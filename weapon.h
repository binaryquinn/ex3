#ifndef WEAPON_H
#define WEAPON_H

#include "combatconstants.h"

class Weapon:public QObject
{
    Q_OBJECT
    Q_ENUMS(Quality)
    Q_ENUMS(WeightClass)
    Q_ENUMS(WeaponTrait)
    Q_PROPERTY(QStringList qualities READ qualities CONSTANT)
    Q_PROPERTY(QStringList weightClasses READ weightClasses CONSTANT)
    Q_PROPERTY(QStringList weaponTraits READ weaponTraits CONSTANT)
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(int damage READ damage CONSTANT)
    Q_PROPERTY(int defense READ defense CONSTANT)
    Q_PROPERTY(int overwhelming READ overwhelming CONSTANT)
    Q_PROPERTY(QString ability READ ability CONSTANT)
    Q_PROPERTY(int accuracy READ accuracy CONSTANT)


public:
    enum WeightClass{Light, Medium, Heavy};
    enum Quality{Mundane,Artifact};
    enum WeaponTrait{ Damage,Overwhelming, Accuracy, Defense};

    explicit Weapon(QObject *parent = 0);
    Weapon(QString name, Quality qual, WeightClass weight, QString abi, CombatConstants::Wounds type = CombatConstants::Bashing, CombatConstants::Range band = CombatConstants::Close, bool useStr = true, bool handed = false, QObject* parent = 0);

    int accuracy(CombatConstants::Range band = CombatConstants::Close) const;
    int damage() const;
    int defense() const;
    QString ability() const;
    void setAbility(const QString &value);

    bool usesStrength() const;
    void setUsesStrength(bool value);

    CombatConstants::Wounds woundType() const;
    void setWoundType(CombatConstants::Wounds value);

    int overwhelming() const;

    QString name() const;
    void setName(const QString &value);

    bool is2Handed() const;
    void set2Handed(bool value);

    CombatConstants::Range maximumRange();

    static QStringList qualities();
    static QStringList weightClasses();
    static QStringList weaponTraits();

signals:
    void qualitiesChanged();
    void weightClassesChanged();
    void weaponTraitsChanged();
    void nameChanged();
    void accuracyChanged();
    void damageChanged();


private:
    QString myName;
    Quality myQuality;
    WeightClass myWeight;
    QString myAbility;
    CombatConstants::Wounds myWoundType;
    CombatConstants::Range myRange;
    bool myStrength;
    bool myHanded;
    static QMap<Quality, QMap< WeightClass, QMap<WeaponTrait, int> > > stats;
    static QMap<Quality, QMap< QString, QMap<CombatConstants::Range, int> > > rangeBands;
    static QStringList myWeaponTraits;
    static QStringList myQualities;
    static QStringList myWeightClasses;

    void initialize();
};


#endif // WEAPON_H

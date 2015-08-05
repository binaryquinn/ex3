#ifndef NEWCOMBATANTDIALOG_H
#define NEWCOMBATANTDIALOG_H

#include <QObject>
#include "weapon.h"
#include "combatant.h"

class TraitRating:public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name MEMBER myName NOTIFY nameChanged)
    Q_PROPERTY(unsigned int stat MEMBER myRating NOTIFY ratingChanged)
public:
    explicit TraitRating(QObject *parent = 0);
    TraitRating(QString name, unsigned int rating = 0, QObject *parent = 0);
signals:
    void nameChanged();
    void ratingChanged();
private:
    QString  myName;
    unsigned int myRating;
};


Q_DECLARE_METATYPE(QList<TraitRating*>)
class NewCombatantDialog : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<TraitRating> attributes READ attributes NOTIFY attributesChanged)
    Q_PROPERTY(QQmlListProperty<TraitRating> abilities READ abilities NOTIFY abilitiesChanged)
    Q_PROPERTY(QQmlListProperty<Weapon> weapons READ weapons NOTIFY weaponsChanged)
    Q_PROPERTY(QQmlListProperty<TraitRating> healthLevels READ healthLevels  NOTIFY healthLevelsChanged)
public:
    explicit NewCombatantDialog(QObject *parent = 0);
    ~NewCombatantDialog();
    QQmlListProperty<TraitRating> attributes();
    QQmlListProperty<TraitRating> abilities();
    QQmlListProperty<Weapon> weapons();
    QQmlListProperty<TraitRating> healthLevels();

signals:
    void abilitiesChanged();
    void attributesChanged();
    void weaponsChanged();
    void healthLevelsChanged();
    void combatantMade(Combatant *newbie, bool iniGiven);

public slots:
    void cleanDialog();
    void makeCombatant(QString name, QVariant ini, int soak, int hardness, int penalty);
    void addWeapon(QString name, int qual, int weight, QString ability, int damage, int range);

private:
    QList<TraitRating *> myAbilities;
    QList<TraitRating *> myAttributes;
    QList<Weapon *> myWeapons;
    QList<TraitRating *>  myHLs;
};

#endif // NEWCOMBATANTDIALOG_H

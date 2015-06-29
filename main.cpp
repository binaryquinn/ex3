#include <QApplication>
#include <QInputEvent>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "combattracker.h"
#include "newcombatantdialog.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    qmlRegisterType<Combatant>("Model", 1, 0, "Combatant");
    qmlRegisterType<TraitRating>("Model", 1, 0, "TraitRating");
    qmlRegisterType<Weapon>("Model", 1, 0, "Weapon");
    CombatTracker myTracker(&app);
    NewCombatantDialog myDialog(&app);
    CombatConstants* constants= new CombatConstants();
     Weapon *weapons = new Weapon(&app);
    QObject::connect(&myDialog, &NewCombatantDialog::combatantMade, &myTracker, &CombatTracker::addCombatant);
    std::srand(QTime::currentTime().msec());

    engine.rootContext()->setContextProperty("Tracker", &myTracker);
    engine.rootContext()->setContextProperty("newCombatant", &myDialog);
    engine.rootContext()->setContextProperty("Constants", constants);
    engine.rootContext()->setContextProperty("Weapons",weapons);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    app.exec();
    delete constants;
    delete weapons;
    return 0;
}

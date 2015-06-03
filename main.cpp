#include <QApplication>
#include <QInputEvent>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "combattracker.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<Combatant>("Model",1,0,"Combatant");
    qmlRegisterType<TraitRating>("Model",1,0,"TraitRating");
    qmlRegisterType<Weapon>("Model",1,0,"Weapon");

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("Tracker", new CombatTracker());
    engine.rootContext()->setContextProperty("Constants", new CombatConstants());
    engine.rootContext()->setContextProperty("Weapons", new Weapon());
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


    return app.exec();
}

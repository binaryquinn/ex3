#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "combattracker.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<CombatConstants>("Model",1,0,"Constants");
    qmlRegisterType<Combatant>("Model",1,0,"Combatant");

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("Tracker", new CombatTracker());
    engine.rootContext()->setContextProperty("myCons", new CombatConstants());
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


    return app.exec();
}

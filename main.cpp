#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "combattracker.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<CombatConstants>("Model",1,0,"Constants");

CombatTracker *battleTrakcer;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("Tracker", battleTrakcer);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


    return app.exec();
}

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "combatant.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<CombatConstants>("Model",1,0,"Constants");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


    return app.exec();
}

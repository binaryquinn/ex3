#include <QApplication>
#include <QQmlApplicationEngine>
#include "combatant.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

//    QQmlApplicationEngine engine;
 //   engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    Combatant c;

    app.quit();
}

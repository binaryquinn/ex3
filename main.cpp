#include <QApplication>
#include <QInputEvent>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "combattracker.h"
#include "newcombatantdialog.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<Combatant>("Model", 1, 0, "Combatant");
    qmlRegisterType<TraitRating>("Model", 1, 0, "TraitRating");
    qmlRegisterType<Weapon>("Model", 1, 0, "Weapon");
    CombatTracker *myTracker = new CombatTracker(&app);
    NewCombatantDialog *myDialog = new NewCombatantDialog(&app);

    QObject::connect(myDialog, &NewCombatantDialog::combatantMade, myTracker, &CombatTracker::addCombatant);
            std::srand(QTime::currentTime().msec());
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("Tracker", myTracker);
    engine.rootContext()->setContextProperty("newCombatant", myDialog);
    engine.rootContext()->setContextProperty("Constants", new CombatConstants());
    engine.rootContext()->setContextProperty("Weapons", new Weapon(&app));
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

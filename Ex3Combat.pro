TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp \
    combatant.cpp \
    healthtrack.cpp \
    combattracker.cpp \
    combatconstants.cpp \
    weapon.cpp \
    newcombatantdialog.cpp \
    combataction.cpp \
    d10.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    combatant.h \
    healthtrack.h \
    combattracker.h \
    combatconstants.h \
    weapon.h \
    newcombatantdialog.h \
    combataction.h \
    d10.h

DISTFILES +=

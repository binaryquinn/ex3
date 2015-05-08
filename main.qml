import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.0

ApplicationWindow
{
    title: qsTr("Exalted 3rd Edition Combat Tracker")
    width: 800
    height: 480
    visible: true
    menuBar: MenuBar
    {
        Menu
        {
            title: qsTr("&File")
            MenuItem
            {
                text: qsTr("&Open")
            }
            MenuItem
            {
                text: qsTr("E&xit")
                onTriggered: Qt.quit();
            }

        }
    }

    MainForm
    {
        id: mainForm1
        anchors.fill: parent
        addCombatantButton.onClicked: messageDialog.open()
    }

            AddCombatantDialog
            {
                id: messageDialog
                height: 560
                width:600

            }

}

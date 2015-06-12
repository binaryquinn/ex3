import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1

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

ColumnLayout {
    id: columnLayout1
    width: parent.width/5
    anchors.bottom: parent.bottom
    anchors.bottomMargin: 10
    anchors.top: parent.top
    anchors.topMargin: 10
    anchors.left: parent.left
    anchors.leftMargin: 10

    ListView {
        id: currentRoundView
        anchors.bottom: addCombatantButton.top
        anchors.bottomMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 5
        anchors.left: parent.left
        anchors.leftMargin: 5
        delegate: Item {
            x: 5
            width: 80
            height: 40
            Row {
                id: row1
                spacing: 10
                Text {
                    text: name + " ("+ initiative + ")"
                    font.bold: true
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
        }
        model: (!!Tracker)? Tracker.currentRound : 0
    }


    Button {
        id: addCombatantButton
        text: qsTr("Add Combatant")
        anchors.bottom: parent.verticalCenter
        anchors.bottomMargin: 5
        onClicked: messageDialog.open()
    }

    Button {
        id: combatControlButton
        text: Tracker.inBattle?qsTr("Stop Combat") : qsTr("Start Combat");
        anchors.top: parent.verticalCenter
        anchors.topMargin: 5
        onClicked: Tracker.inBattle = !Tracker.inBattle
    }

    ListView {
        id: nextRoundView
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.top: combatControlButton.bottom
        anchors.topMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 5
        anchors.left: parent.left
        anchors.leftMargin: 5
        delegate: Item {
            x: 5
            width: 80
            height: 40
            Row {
                id: row2
                spacing: 10
                Text {
                    text: name
                    font.bold: true
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
        }
        model: (!!Tracker)? Tracker.nextRound : 0
    }
}

AttackerPanel{
    id: attackerPanel1
    anchors.bottom: parent.bottom
    anchors.bottomMargin: 10
    anchors.top: parent.top
    anchors.topMargin: 10
    anchors.right: parent.right
    anchors.rightMargin: 10
    anchors.left: columnLayout1.right
    anchors.leftMargin: 10
}

AddCombatantDialog
{
    id: messageDialog
    height: 560
    width:600
    onVisibleChanged:if(!visible) messageDialog.clearFields();
}

}

import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1

Window
{
    id: window1
    title: qsTr("Exalted 3rd Edition Combat Tracker")
    width: 850
    height: 480
    visible: true


    ColumnLayout {
        id: columnLayout1
        width: parent.width/5
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10



        GroupBox {
            id: currentRoundGroup
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.bottom: addCombatantButton.top
            anchors.bottomMargin: 5
            title: qsTr("Current Round")

            ScrollView{
                anchors.fill: parent

                ListView {
                    id: currentRoundView
                    anchors.fill: parent
                    model:(!!Tracker)?Tracker.currentTicks:0
                    delegate: Item{
                        width: 80
                        height: 30
                        Row{
                            spacing: 10
                            id: row1

                            Text {
                                width: 80
                                height: 40
                                text:modelData
                            }
                        }
                    }
                }
            }
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
            //enabled:
            onClicked: Tracker.inBattle = !Tracker.inBattle
        }

        GroupBox {
            id: nextRoundGroup
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: combatControlButton.bottom
            anchors.topMargin: 5
            title: qsTr("Next Round")
            ScrollView
            {
                anchors.fill: parent
                ListView {
                    id: nextRoundView
                    anchors.fill: parent
                    delegate: Item {
                        x: 5
                        width: 80
                        height: 40

                        Row {
                            id: row2
                            spacing: 10
                            Text {
                                text: name + " ("+ initiative + ")"
                                font.bold: true
                                anchors.verticalCenter: parent.verticalCenter
                            }
                        }
                    }
                    model: (!!Tracker)? Tracker.nextRound : 0

                }
            }
        }
    }
    ScrollView{
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: columnLayout1.right
        anchors.leftMargin: 10

        ListView
        {
            anchors.fill: parent
            enabled:Tracker.inBattle
            model:Tracker.currentRound
            delegate:
                AttackerPanel{
                id: attackerPanel1
                attacker:model
                number: index

            }
        }
    }
    AddCombatantDialog
    {
        id: messageDialog
        height: 560
        width:600
        onVisibleChanged:if(!visible) messageDialog.clearFields();
    }

}

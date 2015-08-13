import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1

Window
{
    id: window1
    title: qsTr("Exalted 3rd Edition Combat Tracker")
    width: 1000
    height: 480
    visible: true
    
    
    ColumnLayout {
        id: columnLayout1
        width: parent.width/7
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
            anchors.bottom: buttonPanel.top
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
        
   Item{
        id:buttonPanel
        anchors.centerIn: parent
        Button {
            id: addCombatantButton
            text: qsTr("Add Combatant")
            anchors.bottom: parent.verticalCenter
            anchors.bottomMargin: 5
            anchors.left: parent.left
            onClicked: messageDialog.open()
        }
        Button {
            id: commitButton
            text: qsTr("Commit")
            anchors.top: addCombatantButton.top
            anchors.bottom: combatControlButton.bottom
            anchors.left: addCombatantButton.right
            anchors.leftMargin: 10
//            anchors.right: parent.right
        }
        Button {
            id: combatControlButton
            text: Tracker.inBattle?qsTr("Stop Combat") : qsTr("Start Combat");
            anchors.top: parent.verticalCenter
            anchors.topMargin: 5
            anchors.right: commitButton.left
            enabled: (Tracker.currentTicks.length > 1 || Tracker.currentRound.length > 1)
            onClicked: Tracker.inBattle = !Tracker.inBattle
        }
   }
        GroupBox {
            id: nextRoundGroup
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: buttonPanel.bottom
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
                width: parent.width - 10
                
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

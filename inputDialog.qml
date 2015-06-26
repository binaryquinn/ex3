import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.2
import Model 1.0

Dialog {

    property alias attackerName: label1.text
    property alias attackerAmount: attackerAmountSpinner.value
    property int attackerDirection: (attackerVerbCombo.currentIndex < 1)?1:-1
    property alias attackerUnit: attackerUnitCombo.currentIndex
    property alias attackerDone: doneCheck.checked

    property int defenderIndex:0
    property alias defenderName: label2.text
    property alias defenderAmount: defenderAmountSpinner.value
    property int defenderDirection:(defenderVerbCombo.currentIndex < 1)?1:-1
    property alias defenderUnit: defenderUnitCombo.currentIndex


    contentItem:Item{
        width: 400
        height: 50

        Column {
            id: columnLayout1
            anchors.fill: parent

            GroupBox {
                id: attackerBox
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                title: qsTr("Attacker")

                Row{
                    id: rowLayout1
                    spacing: 5
                    anchors.fill: parent

                    Label {
                        id: label1
                        width: 100


                    }

                    ComboBox {
                        id: attackerVerbCombo
                        model: Constants.verbs
                        width:75
                    }

                    SpinBox {
                        id: attackerAmountSpinner
                        width: 50
                        minimumValue: 0
                        value: 0
                    }

                    ComboBox {
                        id: attackerUnitCombo
                        model: Constants.units
                        width:100
                    }

                    CheckBox{
                        id:doneCheck
                        text: "done?"
                        checked: true
                    }
                }
            }

            GroupBox {
                id: defenderBox

                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                title: qsTr("Defender")

                Row {
                    id: rowLayout2
                    spacing: 5
                    anchors.fill: parent

                    Label {
                        id: label2
                        width: 100

                    }

                    ComboBox {
                        id: defenderVerbCombo
                        model: Constants.verbs
                        width:75
                        currentIndex: model.length-1
                    }

                    SpinBox {
                        id: defenderAmountSpinner
                        width: 50
                        minimumValue: 0
                        value: 0
                    }

                    ComboBox {
                        id: defenderUnitCombo
                        model: Constants.units
                        width:100
                    }
                }
            }

            Row{
                id: rowLayout3
                width: 160
                height: 40
                anchors.rightMargin: 5
                spacing: 10
                anchors.right: parent.right

                Button {
                    id: button1
                    text: qsTr("OK")
                    onClicked: accept();
                }

                Button {
                    id: button2
                    text: qsTr("Cancel")
                    onClicked: reject();
                }
            }
        }
    }
}

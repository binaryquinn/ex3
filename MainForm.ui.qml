import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

Item {
    width: 800
    height: 480
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
            width: 110
            height: 160
            anchors.bottom: parent.verticalCenter
            anchors.bottomMargin: 5
            delegate: Item {
                x: 5
                width: 80
                height: 40
                Row {
                    id: row1
                    spacing: 10
                    Rectangle {
                        width: 40
                        height: 40
                        color: colorCode
                    }

                    Text {
                        text: name
                        font.bold: true
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }
            }
            model: ListModel {
                ListElement {
                    name: "Grey"
                    colorCode: "grey"
                }

                ListElement {
                    name: "Red"
                    colorCode: "red"
                }

                ListElement {
                    name: "Blue"
                    colorCode: "blue"
                }

                ListElement {
                    name: "Green"
                    colorCode: "green"
                }
            }
        }

        ListView {
            id: nextRoundView
            width: 110
            height: 160
            anchors.top: parent.verticalCenter
            anchors.topMargin: 5
            delegate: Item {
                x: 5
                width: 80
                height: 40
                Row {
                    id: row2
                    spacing: 10
                    Rectangle {
                        width: 40
                        height: 40
                        color: colorCode
                    }

                    Text {
                        text: name
                        font.bold: true
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }
            }
            model: ListModel {
                ListElement {
                    name: "Grey"
                    colorCode: "grey"
                }

                ListElement {
                    name: "Red"
                    colorCode: "red"
                }

                ListElement {
                    name: "Blue"
                    colorCode: "blue"
                }

                ListElement {
                    name: "Green"
                    colorCode: "green"
                }
            }
        }
    }
    AddCombatantDialog {
        id: attackerPanel1
        anchors.bottom: parent.bottom
     anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 9
        anchors.right: parent.right
     anchors.rightMargin: 0
        anchors.left: columnLayout1.right
        anchors.leftMargin: 15
    }


}

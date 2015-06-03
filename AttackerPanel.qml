import QtQuick 2.4
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.0

Item {
    id: item1
    width: 600
    height: 250


    ListModel {
        id:tempModel
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

    Component
    {
        id: highlightBar

        Rectangle
        {
            id:highlightRect
            width: 0
            height: 50
            color:!!parent && parent.parent.activeFocus?"#FFFF88":"#FFFFDD";
            y: (!!parent && parent.currentItem !== undefined)? parent.currentItem.y : 0;

        }

    }

    Label {
        id: nameLabel
        text: (Tracker.currentRound[0] !== undefined)? qsTr("Name: ") + Tracker.currentRound[0].name : qsTr("Name: ")
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 10
    }

    Label {
        id: initiativeLabel
        text: (Tracker.currentRound[0] !== undefined)? qsTr("Initiave: ") + Tracker.currentRound[0].initiative : qsTr("Initiave: ")
        anchors.top: nameLabel.bottom
        anchors.topMargin: 5
        anchors.left: parent.left
        anchors.leftMargin: 10
    }

    Label {
        id: nSoakLabel
        text: (Tracker.currentRound[0] !== undefined)? qsTr("Natural Soak: ") + Tracker.currentRound[0].stamina : qsTr("Natural Soak: ")
        anchors.top: initiativeLabel.bottom
        anchors.topMargin: 5
        anchors.left: parent.left
        anchors.leftMargin: 10
    }

    Label {
        id: aSoakLabel
        x: 111
        text: (Tracker.currentRound[0] !== undefined)? qsTr("Armor Soak: ") + Tracker.currentRound[0].armor[0] : qsTr("Armor Soak: ")
        anchors.top: nSoakLabel.top
        anchors.topMargin: 0
    }

    Label {
        id: totalSoakLabel
        x: 220
        text: (Tracker.currentRound[0] !== undefined)? qsTr("Total Soak: ") + (Tracker.currentRound[0].armor[0] + Tracker.currentRound[0].stamina) : qsTr("Total Soak: ")
        anchors.top: nSoakLabel.top
        anchors.topMargin: 0
    }

    Label {
        id: doWhatLabel
        x: 28
        y: 150
        text: qsTr("Do What?")
        anchors.bottom: doWhatScroll.top
        anchors.bottomMargin: 5
        anchors.horizontalCenter: doWhatScroll.horizontalCenter
    }

    ScrollView {
        id: doWhatScroll
        width: (item1.width/3)-40
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.top: parent.verticalCenter
        anchors.topMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 10

        ListView {
            id: doWhatView
            anchors.fill: parent
            delegate: Item {
                x: 5
                width: parent.width
                height: 40
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            doWhatView.currentIndex = index;
                        }
                    Label{
                        text: modelData
                        font.bold: true
                        anchors.verticalCenter: parent.verticalCenter

                       }
                }
            }
            model:Tracker.actions
            highlight: highlightBar
            Component.onCompleted: currentIndex = -1;
        }
    }



    Label {
        id: toWhomLabel
        x: 169
        y: 150
        text: qsTr("To Whom?")
        anchors.bottom: rectangle2.top
        anchors.bottomMargin: 5
        anchors.horizontalCenter: rectangle2.horizontalCenter
    }


    ScrollView{
        id: rectangle2
        x: 138
        width: doWhatScroll.width
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.top: parent.verticalCenter
        anchors.topMargin: 0

        ListView {
            id: listView2
            anchors.fill: parent
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
            model:Tracker.targets
        }
    }


    Label {
        id: withWhatlabel
        x: 299
        y: 150
        text: qsTr("With What?")
        anchors.bottom: rectangle3.top
        anchors.bottomMargin: 5
        anchors.horizontalCenter: rectangle3.horizontalCenter
    }

    ScrollView {
        id: rectangle3
        x: 272
        width: doWhatScroll.width
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.top: parent.verticalCenter
        anchors.topMargin: 0

        ListView {
            id: listView3
            anchors.fill: parent
            delegate: Item {
                x: 5
                width: 80
                height: 40
                Row {
                    id: row3
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
            model:tempModel
        }
    }

}



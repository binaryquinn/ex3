import QtQuick 2.4
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.0
import Model 1.0

Item{

id: item1
property var attacker
property var number

width: 600
height: 200

Rectangle{
    id:rect1
    width: item1.width
    height: item1.height - 5


    border.width: 1




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


    Label{
        id: nameLabel
        text: (attacker !== undefined)? qsTr("Name: ") + attacker.name : qsTr("Name: ")
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 10
    }

    Label{
        id: initiativeLabel
        text: (attacker !== undefined)? qsTr("Initiave: ") + attacker.initiative : qsTr("Initiave: ")
        anchors.top: nameLabel.bottom
        anchors.topMargin: 5
        anchors.left: parent.left
        anchors.leftMargin: 10
    }

    Label{
        id: nSoakLabel
        text: (attacker !== undefined)? qsTr("Natural Soak: ") + attacker.stamina : qsTr("Natural Soak: ")
        anchors.top: initiativeLabel.bottom
        anchors.topMargin: 5
        anchors.left: parent.left
        anchors.leftMargin: 10
    }

    Label{
        id: aSoakLabel
        text: (attacker !== undefined)? qsTr("Armor Soak: ") + attacker.armor[0] : qsTr("Armor Soak: ")
        anchors.top: nSoakLabel.top
        anchors.topMargin: 0
        anchors.left:nSoakLabel.right
        anchors.leftMargin: 10
    }

    Label{
        id: totalSoakLabel
        text: (attacker !== undefined)? qsTr("Total Soak: ") + (attacker.armor[0] + attacker.stamina) : qsTr("Total Soak: ")
        anchors.top: nSoakLabel.top
        anchors.topMargin: 0
        anchors.left:aSoakLabel.right
        anchors.leftMargin: 10

    }

    Label {
        id: woundLabel
        text: (attacker !== undefined)? qsTr("Wound Penalty: ") + attacker.woundPenalty : qsTr("Wound Penalty: 0")
        anchors.top: nSoakLabel.bottom
        anchors.topMargin: 5
        anchors.left: parent.left
        anchors.leftMargin: 10
    }
    Label {
        id: healthLabel
        text: (attacker !== undefined)? qsTr("Health: ") + attacker.health : qsTr("Health: ")
        anchors.top: woundLabel.top
        anchors.topMargin: 0
        anchors.left: woundLabel.right
        anchors.leftMargin: 10
    }

//    Label{
//        id: doWhatLabel
//        x: 28
//        y: 150
//        text: qsTr("Do What?")
//        anchors.bottom: doWhatScroll.top
//        anchors.bottomMargin: 5
//        anchors.horizontalCenter: doWhatScroll.horizontalCenter
//    }

//    ScrollView{
//        id: doWhatScroll
//        width: (item1.width/3)-40
//        anchors.bottom: parent.bottom
//        anchors.bottomMargin: 10
//        anchors.top: parent.verticalCenter
//        anchors.topMargin: 0
//        anchors.left: parent.left
//        anchors.leftMargin: 10

//        ListView{
//            id: doWhatView
//            visible: false
//            anchors.fill: parent
//            delegate: Item{
//                x: 5
//                width: parent.width
//                height: 40
//                    MouseArea{
//                        anchors.fill: parent
//                        onClicked: {
//                            doWhatView.currentIndex = index;
//                        }
//                        Label{
//                            text: modelData
//                            font.bold: true
//                            anchors.verticalCenter: parent.verticalCenter

//                       }
//                }
//            }
//            model:(Tracker.currentRound[0] !== undefined)? Tracker.currentRound[0].actions : 0;
//            onModelChanged: currentIndex = -1;
//            highlight: highlightBar
//            Component.onCompleted: currentIndex = -1;
//        }
//    }



    Label{
        id: toWhomLabel
        text: qsTr("To Whom?")
        anchors.bottom: toWhomScroll.top
        anchors.bottomMargin: 5
        anchors.horizontalCenter: toWhomScroll.horizontalCenter
    }


    ScrollView{
        id: toWhomScroll
        width: (rect1.width/3)-40
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.top: parent.verticalCenter
        anchors.topMargin: 0

        ListView{
            id: toWhomView
            anchors.fill: parent
           model:(attacker !== undefined)?attacker.targets:0
            delegate: Item {
                x: 5
                width: parent.width
                height: 40

                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        toWhomView.currentIndex = index;
                    }
                    Label{
                        text: name + " ("+ initiative + ")"
                        font.bold: true
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }
            }

            onModelChanged:
            {
//                doWhatView.currentIndex = -1;
                currentIndex = -1;
//                withWhatView.currentIndex = -1;
            }
            highlight: highlightBar
            Component.onCompleted:{


                currentIndex = -1;
            }
        }
    }


//    Label{
//        id: withWhatlabel
//        x: 299
//        y: 150
//        text: qsTr("With What?")
//        anchors.bottom: withWhatScroll.top
//        anchors.bottomMargin: 5
//        anchors.horizontalCenter: withWhatScroll.horizontalCenter
//    }

//    ScrollView{
//        id: withWhatScroll
//        width: doWhatScroll.width
//        visible: false
//        anchors.left: toWhomScroll.right
//        anchors.leftMargin: 10
//        anchors.bottom: parent.bottom
//        anchors.bottomMargin: 10
//        anchors.top: parent.verticalCenter
//        anchors.topMargin: 0

//        ListView{
//            id: withWhatView
//            anchors.fill: parent
//            delegate: Item {
//                x: 5
//                width: parent.width
//                height: 40
//                    MouseArea{
//                        anchors.fill: parent
//                        onClicked: {
//                            withWhatView.currentIndex = index;
//                        }
//                        Label{
//                            text: modelData
//                            font.bold: true
//                            anchors.verticalCenter: parent.verticalCenter

//                       }
//                }
//            }
//            model:(Tracker.currentRound[0] !== undefined)? Tracker.currentRound[0].weaponry : 0
//            onModelChanged: currentIndex = -1;
//            highlight: highlightBar
//            Component.onCompleted: currentIndex = -1;

//        }
//    }

    Button {
        id: commitButton

        text: qsTr("Commit")
        anchors.verticalCenter: toWhomScroll.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 10

        width:50
        enabled: (toWhomView.currentIndex > -1)//(doWhatView.currentIndex > -1)&& &&(withWhatView.currentIndex > -1)
        onClicked:
        {
            actionDialog.defenderIndex = toWhomView.currentIndex
            actionDialog.attackerName = attacker.name;
            actionDialog.defenderName =  attacker.targets[toWhomView.currentIndex].name;
            actionDialog.open();
        }

    }
    InputDialog
    {
        id: actionDialog
        width: 400
        height: 200
        onAccepted:
        {
            Tracker.modifyCombatants(number, attackerUnit, attackerAmount*attackerDirection, attackerDone, defenderIndex, defenderUnit, defenderAmount * defenderDirection);
        }

    }

}


}
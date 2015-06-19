import QtQuick 2.4
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.0

Item{
    id: item1
    width: 600
    height: 250

    enabled: Tracker.inBattle

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
        text: (Tracker.currentRound[0] !== undefined)? qsTr("Name: ") + Tracker.currentRound[0].name : qsTr("Name: ")
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 10
    }

    Label{
        id: initiativeLabel
        text: (Tracker.currentRound[0] !== undefined)? qsTr("Initiave: ") + Tracker.currentRound[0].initiative : qsTr("Initiave: ")
        anchors.top: nameLabel.bottom
        anchors.topMargin: 5
        anchors.left: parent.left
        anchors.leftMargin: 10
    }

    Label{
        id: nSoakLabel
        text: (Tracker.currentRound[0] !== undefined)? qsTr("Natural Soak: ") + Tracker.currentRound[0].stamina : qsTr("Natural Soak: ")
        anchors.top: initiativeLabel.bottom
        anchors.topMargin: 5
        anchors.left: parent.left
        anchors.leftMargin: 10
    }

    Label{
        id: aSoakLabel
        x: 111
        text: (Tracker.currentRound[0] !== undefined)? qsTr("Armor Soak: ") + Tracker.currentRound[0].armor[0] : qsTr("Armor Soak: ")
        anchors.top: nSoakLabel.top
        anchors.topMargin: 0
    }

    Label{
        id: totalSoakLabel
        x: 220
        text: (Tracker.currentRound[0] !== undefined)? qsTr("Total Soak: ") + (Tracker.currentRound[0].armor[0] + Tracker.currentRound[0].stamina) : qsTr("Total Soak: ")
        anchors.top: nSoakLabel.top
        anchors.topMargin: 0
    }

    Label {
        id: woundLabel
        text: (Tracker.currentRound[0] !== undefined)? qsTr("Wound Penalty: ") + Tracker.currentRound[0].woundPenalty : qsTr("Wound Penalty: 0")
        anchors.top: nSoakLabel.bottom
        anchors.topMargin: 5
        anchors.left: parent.left
        anchors.leftMargin: 10
    }

    Label{
        id: doWhatLabel
        x: 28
        y: 150
        text: qsTr("Do What?")
        anchors.bottom: doWhatScroll.top
        anchors.bottomMargin: 5
        anchors.horizontalCenter: doWhatScroll.horizontalCenter
    }

    ScrollView{
        id: doWhatScroll
        width: (item1.width/3)-40
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.top: parent.verticalCenter
        anchors.topMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 10

        ListView{
            id: doWhatView
            visible: false
            anchors.fill: parent
            delegate: Item{
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
            model:(Tracker.currentRound[0] !== undefined)? Tracker.currentRound[0].actions : 0;
            onModelChanged: currentIndex = -1;
            highlight: highlightBar
            Component.onCompleted: currentIndex = -1;
        }
    }



    Label{
        id: toWhomLabel
        x: 169
        y: 150
        text: qsTr("To Whom?")
        anchors.bottom: toWhomScroll.top
        anchors.bottomMargin: 5
        anchors.horizontalCenter: toWhomScroll.horizontalCenter
    }


    ScrollView{
        id: toWhomScroll
        width: doWhatScroll.width
        anchors.left: doWhatScroll.right
        anchors.leftMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.top: parent.verticalCenter
        anchors.topMargin: 0

        ListView{
            id: toWhomView
            anchors.fill: parent
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
                        text: name
                        font.bold: true
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }
            }
            model:Tracker.targets
            onModelChanged:
            {
                doWhatView.currentIndex = -1;
                currentIndex = -1;
                withWhatView.currentIndex = -1;
            }
            highlight: highlightBar
            Component.onCompleted: currentIndex = -1;

        }
    }


    Label{
        id: withWhatlabel
        x: 299
        y: 150
        text: qsTr("With What?")
        anchors.bottom: withWhatScroll.top
        anchors.bottomMargin: 5
        anchors.horizontalCenter: withWhatScroll.horizontalCenter
    }

    ScrollView{
        id: withWhatScroll
        width: doWhatScroll.width
        visible: false
        anchors.left: toWhomScroll.right
        anchors.leftMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.top: parent.verticalCenter
        anchors.topMargin: 0

        ListView{
            id: withWhatView
            anchors.fill: parent
            delegate: Item {
                x: 5
                width: parent.width
                height: 40
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            withWhatView.currentIndex = index;
                        }
                        Label{
                            text: modelData
                            font.bold: true
                            anchors.verticalCenter: parent.verticalCenter

                       }
                }
            }
            model:(Tracker.currentRound[0] !== undefined)? Tracker.currentRound[0].weaponry : 0
            onModelChanged: currentIndex = -1;
            highlight: highlightBar
            Component.onCompleted: currentIndex = -1;

        }
    }

    Button {
        id: commitButton
        y: 171
        text: qsTr("Commit")
        anchors.verticalCenter: withWhatScroll.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: withWhatScroll.right
        anchors.leftMargin: 10

        enabled: (toWhomView.currentIndex > -1)//(doWhatView.currentIndex > -1)&& &&(withWhatView.currentIndex > -1)
        onClicked:
        {
            actionDialog.defenderIndex = toWhomView.currentIndex
            actionDialog.attackerName = Tracker.currentRound[0].name;
            actionDialog.defenderName =  Tracker.targets[toWhomView.currentIndex].name;
            actionDialog.open();

//            if(Tracker.currentRound[0].actions[doWhatView.currentIndex].contains("Attack"))
//            {
//                defenderDialog.model = Tracker.targets[toWhomView.currentIndex].defenseList;
//                defenderDialog.open();
//            }
        }
    }

    DefenderChoiceDialog
    {
        id:defenderDialog
        width: 300
        height: 300
        onAccepted:
        {

            var attacker = 0;
            var aWeapon = withWhatView.currentIndex;
            var defender = toWhomView.currentIndex;
            var dWeapon = (defenderDialog.choice==0)? 0 : (defenderDialog.choice-1);
            var aType = (doWhatView.currentIndex== 0)? 0 : 1;
            var dType = (defenderDialog.choice==0)? 1: 2;
            Tracker.attack(attacker, aWeapon, defender, dWeapon, aType, dType);
        }
    }

    InputDialog
    {
        id: actionDialog
        width: 400
        height: 200
        onAccepted:
        {
            Tracker.modifyCombatant(0, true, attackerUnit, attackerAmount*attackerDirection, attackerDone);
            Tracker.modifyCombatant(defenderIndex, false, defenderUnit, defenderAmount * defenderDirection, false);
        }

    }


}



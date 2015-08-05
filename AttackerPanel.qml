import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import Model 1.0
import QtQuick.Extras 1.4
import QtQuick.Controls.Styles 1.2

Item{

    id: item1
    property var attacker
    property int number


    height: 200

    Rectangle{
        id:rect1
        width: item1.width
        height: item1.height - 5


        border.width: 1

        Label{
            id: nameLabel
            height: doWhatCombo.height
            text: (attacker !== undefined)? qsTr("Name: ") + attacker.name  + " (" + attacker.initiative + ")" : qsTr("Name: ")
            horizontalAlignment: Text.AlignHCenter
            anchors.right: doWhatCombo.left
            anchors.rightMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.top: parent.top
            anchors.topMargin: 10
        }

        ComboBox
        {
            id:doWhatCombo
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top : nameLabel.top
            model: (attacker !== undefined)?attacker.actions:0
            width:150
            textRole:"name"
            style:ComboBoxStyle
            {
                label:Label
                {
                    text:(doWhatCombo.currentIndex == -1)? "do What?":doWhatCombo.currentText
                }
            }
            Component.onCompleted: currentIndex = -1
            onVisibleChanged: currentIndex = -1
        }


        ComboBox {
        id: toWhomCombo
        visible:doWhatCombo.currentIndex > -1 && attacker.actions[doWhatCombo.currentIndex].targetting !== CombatConstants.Self
        anchors.left: doWhatCombo.right
        anchors.leftMargin: 10
        anchors.top: doWhatCombo.top
        anchors.topMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 10
        model:attacker.targets
        textRole: "name"
        style:ComboBoxStyle
        {
            label:Label
            {
                text:(toWhomCombo.currentIndex == -1)? "To Whom?":toWhomCombo.currentText
            }
        }
        Component.onCompleted: currentIndex = -1
        onVisibleChanged: currentIndex = -1
        onCurrentIndexChanged: withWhatCombo.currentIndex = -1
    }

    Item {
        id: item2

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5
        anchors.right: doWhatCombo.left
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 5
        anchors.top: nameLabel.bottom
        anchors.topMargin: 5
        visible: doWhatCombo.currentIndex > -1

        ComboBox {
            id: withWhatCombo
            anchors.topMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.top: parent.top
            anchors.margins: 5

            model:attacker.weaponry
            textRole: "name"
            visible: doWhatCombo.currentIndex > -1 && toWhomCombo.currentIndex > -1 && attacker.actions[doWhatCombo.currentIndex].usesWeapon
            style:ComboBoxStyle
            {
                label:Label
                {
                    text:(withWhatCombo.currentIndex == -1)? "With What?":withWhatCombo.currentText
                }
            }
            Component.onCompleted: currentIndex = -1
            onVisibleChanged: currentIndex = -1
        }

        RollMethodPanel {
            id: rollMethodPanel1
            visible: doWhatCombo.currentIndex > -1 && attacker.actions[doWhatCombo.currentIndex].rolledAction && (!attacker.actions[doWhatCombo.currentIndex].usesWeapon || withWhatCombo.currentIndex > -1)
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            penalty: attacker.woundPenalty
            base: visible? Tracker.dicePool(attacker, doWhatCombo.currentIndex, attacker.initiative > 0, 0, withWhatCombo.currentIndex) : 0
            text:visible? (" Base Pool ( " + Tracker.dicePoolString(number, doWhatCombo.currentIndex, attacker.initiative > 0, 0, withWhatCombo.currentIndex) + "): " + base ) : ""
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.top: withWhatCombo.bottom
            anchors.topMargin: 5
            onResult:{
                            var rollResult = (method)? value : Tracker.roll(value)

            }
        }
    }
    Item {
        id: item3
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: item2.top
        anchors.topMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 5
        anchors.left: toWhomCombo.left
        anchors.leftMargin: 0

        ComboBox {
            id: defenderCombo
            anchors.topMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.top: parent.top
            anchors.margins: 5

            visible: doWhatCombo.currentIndex > -1 && toWhomCombo.currentIndex > -1 && attacker.actions[doWhatCombo.currentIndex].difficulty ==="defense"
            model: visible? attacker.targets[toWhomCombo.currentIndex].defenseList:0
            style:ComboBoxStyle
            {
                label:Label
                {
                    text:(defenderCombo.currentIndex == -1)? "Attempts to...":defenderCombo.currentText
                }
            }
            Component.onCompleted: currentIndex = -1
            onVisibleChanged: currentIndex = -1
        }

        RollMethodPanel
        {
            id:reactiveRollPanel
            visible: doWhatCombo.currentIndex > -1 && toWhomCombo.currentIndex > -1 && attacker.actions[doWhatCombo.currentIndex].contested
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            penalty: visible?attacker.targets[toWhomCombo.currentIndex].woundPenalty:0
            base: visible? Tracker.dicePool(toWhomCombo.currentIndex, doWhatCombo.currentIndex, attacker.initiative > 0, 1, defenderCombo.currentIndex) : 0
            text:visible? (" Base Pool ( " + Tracker.dicePoolString(toWhomCombo.currentIndex, doWhatCombo.currentIndex, attacker.initiative > 0, 1, withWhatCombo.currentIndex) + "): " + base ) : ""
            anchors.right: parent.right
            anchors.rightMargin: 0
        }

    }
}



}

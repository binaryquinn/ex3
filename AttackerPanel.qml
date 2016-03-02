import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import Model 1.0
import QtQuick.Controls.Styles 1.2

Rectangle{
    id:rect1
    border.width: 1
    property var attacker
    property int number
    readonly property var action: (doWhatCombo.currentIndex > -1)? attacker.actions[doWhatCombo.currentIndex] : 0
    readonly property var defender: (toWhomCombo.currentIndex > -1)? attacker.targets[toWhomCombo.currentIndex] : 0
    property bool complete:((!!action)?
                                (action.targetting === CombatConstants.Self || !!defender)
                                && (!action.usesWeapon || withWhatCombo.currentIndex > -1)
                                && (!defenderCombo.visible || defenderCombo.currentIndex > -1 )
//                                && (!action.rolledAction || rollChoice.visible)
                              :  false)

    signal actionResults(var index, var values);
    height: 250

    Item{
        id: item1
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: lockInSwitch.top
        anchors.margins: 5
        anchors.top: parent.top
        enabled: !lockInSwitch.checked
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

        ComboBox {
            id:doWhatCombo
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top : nameLabel.top
            model: (attacker !== undefined)?attacker.actions:0
            width:150
            textRole:"name"
            style:ComboBoxStyle {
                label:Label {
                    text:(doWhatCombo.currentIndex == -1)? "do What?":doWhatCombo.currentText
                }
            }
            Component.onCompleted: currentIndex = -1
            onVisibleChanged: currentIndex = -1
        }


        ComboBox {
            id: toWhomCombo
            visible:!!action && action.targetting !== CombatConstants.Self
            anchors.left: doWhatCombo.right
            anchors.leftMargin: 10
            anchors.top: doWhatCombo.top
            anchors.topMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 10
            model:attacker.targets
            textRole: "name"
            style:ComboBoxStyle {
                label:Label {
                    text:(toWhomCombo.currentIndex == -1)? "To Whom?":toWhomCombo.currentText
                }
            }
            Component.onCompleted: currentIndex = -1
            onCurrentIndexChanged: withWhatCombo.currentIndex = -1
            onVisibleChanged: currentIndex = -1

        }

        Item{
            id: item2
            anchors.right: doWhatCombo.left
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.top: nameLabel.bottom
            anchors.topMargin: 5
            visible: doWhatCombo.currentIndex > -1

            ComboBox {
                id: withWhatCombo
                anchors.right: parent.right
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.margins: 5

                model:attacker.weaponry
                textRole: "name"
                visible: doWhatCombo.currentIndex > -1 && toWhomCombo.currentIndex > -1 && action.usesWeapon
                style:ComboBoxStyle {
                    label:Label {
                        text:(withWhatCombo.currentIndex == -1)? "With What?":withWhatCombo.currentText
                    }
                }
                Component.onCompleted: currentIndex = -1
                onVisibleChanged: currentIndex = -1
            }


            PoolCalcPanel {
                id: proactivePoolPanel
                visible: !!action && action.rolledAction && (!action.usesWeapon || withWhatCombo.currentIndex > -1)
                anchors.left: parent.left
                penalty: attacker.woundPenalty
                base: visible? Tracker.dicePool(attacker, doWhatCombo.currentIndex, attacker.initiative > 0, 0, withWhatCombo.currentIndex) : 0
                text:visible? (" Base Pool ( " + Tracker.dicePoolString(number, doWhatCombo.currentIndex, attacker.initiative > 0, 0, withWhatCombo.currentIndex) + "): " + base ) : ""
                anchors.right: parent.right
                anchors.top: withWhatCombo.bottom
                anchors.margins: 5
                anchors.bottom: parent.bottom
            }
        }
        Item {
            id: item3
            anchors.top: item2.top
            anchors.topMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 5
            anchors.left: toWhomCombo.left
            anchors.leftMargin: 0
            visible: toWhomCombo.currentIndex > -1
            ComboBox {
                id: defenderCombo
                anchors.right: parent.right
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.margins: 5
                visible: doWhatCombo.currentIndex > -1 && toWhomCombo.currentIndex > -1 && action.difficulty && action.difficulty ==="defense"
                model: (!!defender)? defender.defenseList:0
                style:ComboBoxStyle {
                    label:Label {
                        text:(defenderCombo.currentIndex == -1)? "Attempts to...":defenderCombo.currentText
                    }
                }
                Component.onCompleted: currentIndex = -1
                onVisibleChanged: currentIndex = -1
            }

            PoolCalcPanel{
                id:reactivePoolPanel
                visible: doWhatCombo.currentIndex > -1 && toWhomCombo.currentIndex > -1 && action.contested
                anchors.top:defenderCombo.bottom
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                penalty: visible? defender.woundPenalty:0
                base: visible? Tracker.dicePool(toWhomCombo.currentIndex, doWhatCombo.currentIndex, attacker.initiative > 0, 1, defenderCombo.currentIndex) : 0
                text:visible? (" Base Pool ( " + Tracker.dicePoolString(toWhomCombo.currentIndex, doWhatCombo.currentIndex, attacker.initiative > 0, 1, withWhatCombo.currentIndex) + "): " + base ) : ""
            }
        }

        InputPanel{
            id:proactiveInput
            visible: doWhatCombo.currentIndex > -1
            anchors.bottom: doneCheck.top
            anchors.left:parent.left
        }

        CheckBox{
            id: doneCheck
            checked: true;
            text: "done for this round?"
            anchors.bottom: parent.bottom
            anchors.left:parent.left
        }

//        RollMethodPanel{
//            id:rollChoice
//            anchors.top:item2.Bottom
//            anchors.horizontalCenter: parent.horizontalCenter
//            anchors.bottom: parent.bottom
//            visible: action && action.rolledAction && (proactiveInput.visible || reactiveInput.visible)
//        }

        InputPanel{
            id:reactiveInput
            anchors.bottom: parent.bottom
            anchors.right:parent.right
            visible:defender
        }
    }
    Switch {
        visible: complete
        id:lockInSwitch
        style: SwitchStyle {
            groove: Rectangle {
                implicitWidth: control.width
                implicitHeight: control.height
                gradient: Gradient{
                    GradientStop { position: 0.0; color: control.checked?"darkgoldenrod" : "dimgrey"}
                    GradientStop { position: 0.1; color: control.checked?"goldenrod" : "darkgrey"}
                    GradientStop { position: 0.4; color: control.checked?"gold" : "lightgrey" }
                    GradientStop { position: 0.6; color: control.checked?"gold" : "lightgrey" }
                    GradientStop { position: 0.9; color: control.checked?"goldenrod" : "darkgrey"}
                    GradientStop { position: 1.0; color: control.checked?"darkgoldenrod" : "dimgrey"}
                }
                border{
                    width: 1
                    color: "grey"
                }
            }
        }

        width:parent.width - 10
        height:20
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5
        onCheckedChanged: {
            var results;
            if(checked)
            {
                results = {action:doWhatCombo.currentIndex,
                           attacker:{n : number, d:doneCheck.checked,i : proactiveInput.initiativeDamage, h : proactiveInput.healthDamage, w : proactiveInput.woundUnit},
                           defender:(defender)?{n:toWhomCombo.currentIndex, i : reactiveInput.initiativeDamage, h : reactiveInput.healthDamage, w : reactiveInput.woundUnit}:undefined}
            }
            else {
                results = -1
            }
            actionResults(number,results)
        }
    }
}


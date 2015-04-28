import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.2




Item {
    id: item2
    width: 525
    height: 400



    property int longest:0
    property alias addWeaponButton: addWeaponButton
    property alias newWeaponField: newWeaponField
    property alias newAccField: newAccField
    property alias newAtkField: newAtkField
    property alias newDefField: newDefField
    property alias newOverField: newOverField
    property alias  weaponsView: weaponsView

    TextField {
        id: nameField
        anchors.right: armorBox.left
        anchors.rightMargin: 5
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 5
        placeholderText: qsTr("Name")
    }

    GroupBox {
        id: armorBox
        anchors.right: parent.right
        anchors.rightMargin: 5
        anchors.top: parent.top
        anchors.topMargin: 5
        title: qsTr("Armor")

        ColumnLayout {
            id: armorLayout
            anchors.fill: parent

            TextField {
                id: soakField
                placeholderText: qsTr("Soak")
                validator: IntValidator{}
            }

            TextField {
                id: hardnessField
                placeholderText: qsTr("Hardness")
                validator: IntValidator{}
            }

            TextField {
                id: mpField
                placeholderText: qsTr("Mobility Penalty")
                validator: IntValidator{}
            }
        }
    }

    GroupBox {
        id: attributesBox
        anchors{
            left:nameField.left
            bottom: armorBox.bottom
            top: nameField.bottom
            topMargin: 5
        }
        width:nameField.width
        title: qsTr("Attributes")

        ListView {
            id: attributeView
            interactive: false
            anchors.fill: parent
            clip: false
            orientation: ListView.Horizontal
            delegate: Item {
                id: attributeItem
                x: 5
                width: 100
                height: 30
                Row {
                    Label {
                        id: attributeLabel
                        y: 11
                        width: 59
                        height: 20
                        text: name + ":"
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignRight
                    }

                    ComboBox {
                        id: attrRatingBox
                        y: 11
                        width: 30
                        height: 20
                        model: 6
                    }
                }
            }
            model: ListModel {
                ListElement {
                    name: "Strength"
                }
                ListElement {
                    name: "Dexterity"
                }
                ListElement {
                    name: "Stamina"
                }
                ListElement {
                    name: "Wits"
                }
            }


        }
    }
    GroupBox {
        id: abilityBox
        anchors.top: healthBox.top
        anchors.bottom: healthBox.bottom

        width: parent.width/2
        title: qsTr("Abilities")

        GridView {
            id: abilityView
            interactive: false
            anchors.fill: parent
            cellHeight: 30
            cellWidth: 100
            clip: true
            delegate: Item {
                id: abilityItem
                x: 5
                width: 100
                height: 30
                Row {
                    id: row1
                    spacing:5
                    Label {
                        id: abilityLabel
                        y: 11
                        width: 59
                        height: 20
                        text: name + ":"
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignRight
                    }

                    ComboBox {
                        id: abiRatingBox
                        y: 11
                        width: 30
                        height: 20
                        model: 6
                    }
                }
            }
            model: ListModel {
                ListElement {
                    name: "Archery"
                }
                ListElement {
                    name: "Athletics"
                }
                ListElement {
                    name: "Awareness"
                }
                ListElement {
                    name: "Brawl"
                }
                ListElement {
                    name: "Dodge"
                }
                ListElement {
                    name: "Martial Arts"
                }
                ListElement {
                    name: "Melee"
                }
                ListElement {
                    name: "Resistance"
                }
                ListElement {
                    name: "Ride"
                }
                ListElement {
                    name: "Thrown"
                }
            }
        }
    }
    GroupBox
    {
        id:healthBox
        height: 220
        title: "Health Levels"
        anchors.left: parent.horizontalCenter
        anchors.leftMargin: 5
        anchors.right: parent.right
        anchors.rightMargin: 5
        anchors.top: armorBox.bottom
        anchors.topMargin: 5
        ListView {
            id: healthView
            interactive: false
            height: parent.height - 5
            delegate: Item {
                id:hlDelegate
                x: 5
                width: 173
                height: 40
                Row{
                    id: row2
                    spacing: 5

                    Label
                    {
                        id:hlLabel
                        text:penalty
                        anchors.verticalCenter: parent.verticalCenter
                        horizontalAlignment: Text.AlignRight
                        verticalAlignment: Text.AlignVCenter
                        width:longest
                        Component.onCompleted: if(longest < implicitWidth) longest = implicitWidth;

                    }
                    Column
                    {
                        id: column1
                        width: 16
                        height: 32
                        spacing: 0
                        anchors.verticalCenter: parent.verticalCenter
                        Button
                        {
                            id: upButton
                            width: 16
                            height: 16
                            iconSource: "images/Up.png"
                            onClicked: hlRepeater.model++
                        }

                        Button
                        {
                            id: downButton
                            width: 16
                            height: 16
                            iconSource: "images/Down.png"
                            onClicked: if(hlRepeater.model > 0) hlRepeater.model--
                        }
                    }

                    Repeater
                    {
                        id:hlRepeater
                        width: hlDelegate.width - (column1.x + column1.width+5)
                        height: 20
                        model:hlCount
                        anchors.verticalCenter: parent.verticalCenter
                        Image {
                            anchors.verticalCenter: if(!!parent) parent.verticalCenter
                            id: image1
                            width: 18
                            height: 18
                            source: "images/square-empty.png"
                        }
                    }
                }
            }
            model: ListModel {
                ListElement {
                    penalty:"0"
                    hlCount:1
                }

                ListElement {
                    penalty:"-1"
                    hlCount:2
                }

                ListElement {
                    penalty:"-2"
                    hlCount:2
                }
                ListElement {
                    penalty:"-4"
                    hlCount:1
                }
                ListElement {
                    penalty:"Incapacitated"
                    hlCount:1
                }
            }
        }

    }

    GroupBox {
        id: weaponsBox
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: healthBox.bottom
        anchors.margins: 5

        title: qsTr("Weapons")
        Column{
            id: weaponLayout
            anchors.fill: parent
            spacing: 5

            Row {
                id: newWeaponRow
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 5
                TextField {
                    id: newWeaponField
                    placeholderText: qsTr("Weapon Name")
                }

                TextField {
                    id: newAccField
                    width:80
                    placeholderText: qsTr("Accuracy")
                    validator: IntValidator{}
                }

                TextField {
                    id: newAtkField
                    placeholderText: qsTr("Attack")
                    width:80
                    validator: IntValidator{}
                }

                TextField {
                    id: newDefField
                    placeholderText: qsTr("Defense")
                    width:80
                    validator: IntValidator{}
                }

                TextField {
                    id: newOverField
                    placeholderText: qsTr("Overwhelming")
                    width:80
                    validator: IntValidator{}
                }

                Button {
                    id: addWeaponButton
                    width: 25
                    text: qsTr("+")
                }
            }
            TableView{
                id: weaponsView
                height:weaponsBox.height - (newWeaponRow.height+6*parent.spacing)

                anchors.margins: 5
                anchors.right: parent.right
                anchors.left: parent.left
                model:ListModel{}
                TableViewColumn {
                    role: "name"
                    title: "Weapon"
//                    width: 100
                }
                TableViewColumn {
                    role: "acc"
                    title: "Accuracy"
                    width: 80
                }
                TableViewColumn {
                    role: "atk"
                    title: "Attack"
                    width: 80
                }
                TableViewColumn {
                    role: "def"
                    title: "Defense"
                    width: 80
                }
                TableViewColumn {
                    role: "over"
                    title: "Overwhelming"
                    width: 80
                }
            }
        }
    }
}



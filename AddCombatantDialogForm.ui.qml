import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.2
import Model 1.0




Item {
    id: item2
    width: 600
    height: 560

    Constants{
        id:myCons
    }

    property alias nameText: nameField.text
    property alias attributeModel: attributeView.model
    property alias soakText: soakField.text
    property alias hardnessText: hardnessField.text
    property alias mpText: mpField.text
    property alias abilityModel: abilityView.model
    property alias healthModel: healthView.model
    property int longest: 0
    property alias addWeaponButton: addWeaponButton
    property alias newWeaponText: newWeaponField.text
    property alias newAccText: newAccField.text
    property alias newAtkText: newAtkField.text
    property alias newDefText: newDefField.text
    property alias newOverText: newOverField.text
    property alias abilityCombo: abilityCombo
    property alias weaponsModel: weaponsView.model
    property alias okButton: okButton
    property alias cancelButton: cancelButton

    TextField {
        id: nameField
        anchors.right: armorBox.left
        anchors.rightMargin: 5
        anchors.top: parent.top
        anchors.topMargin: 15
        anchors.left: parent.left
        anchors.leftMargin: 10
        placeholderText: qsTr("Name")
        validator: RegExpValidator
        {
            regExp:/\S+.*/
        }
    width:25

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
            clip: true
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
                        model: [1,2,3,4,5]
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
            cellWidth: 120
            clip: true
            delegate: Item {
                id: abilityItem
                x: 5
                width: 120
                height: 30
                Row {
                    id: row1
                    spacing:5
                    Label {
                        id: abilityLabel
                        y: 11
                        width: 80
                        height: 20
                        text: modelData+ ":"
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignRight
                    }

                    ComboBox {
                        id: abiRatingCombo
                        y: 11
                        width: 30
                        height: 20
                        model: 6
                    }
                }
            }
            model: myCons.allAbilities
        }
    }

    GroupBox
    {
        id:healthBox
        height: 200
        title: "Health Levels"
        anchors.left: parent.horizontalCenter
        anchors.leftMargin: 5
        anchors.right: parent.right
        anchors.rightMargin: 5
        anchors.top: armorBox.bottom
        anchors.topMargin: 5
        ScrollView{
            width:parent.width
            height:parent.height
        ListView {
            id: healthView
            interactive: false
            height: parent.height - 5
            delegate:HealthLevelDelegate{}
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
    }

    GroupBox {
        id: weaponsBox
        height: 200
        anchors.rightMargin: 5
        anchors.leftMargin: 5
        anchors.topMargin: 4
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: healthBox.bottom
        anchors.margins: 5

        title: qsTr("Weapons")
        Column{
            id: weaponLayout
            anchors.top: parent.top
            anchors.topMargin: 5
            spacing: 10



            Row {
                    id: weaponTypeRow
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 5
                    TextField {
                        id: newWeaponField
                        width:180
                        height: 25
                        placeholderText: qsTr("Weapon Name")
                        validator: RegExpValidator
                        {
                            regExp:/\S+.*/
                        }


                    }

                    ComboBox {
                        id: abilityCombo
                        model: myCons.combatAbilities
                        width:120
                        style:ComboBoxStyle
                        {
                            label:Label
                            {
                                text:(abilityCombo.currentIndex == -1)? "Ability" : "Ability: " + abilityCombo.currentText
                            }
                        }
                        Component.onCompleted: currentIndex = -1
                    }
                    ComboBox {
                        id: rangeCombo
                        enabled: false
                        width:160
                        model:myCons.ranges
                        style:ComboBoxStyle
                        {
                            label:Label
                            {
                                text:(rangeCombo.currentIndex == -1)? "Maximum Range":"Maximum Range: " + rangeCombo.currentText
                            }
                        }
                        Component.onCompleted: currentIndex = -1
                    }

                    Button {
                        id: addWeaponButton
                        width: 25
                        text: qsTr("+")
                        enabled: newWeaponText.length > 0
                    }
                }

            Row {
                    id: weaponStatRow
                    width: 200
                    height: 23
                    anchors.left: weaponTypeRow.left
                    anchors.leftMargin: 0
                    spacing: 5
                    TextField {
                        id: newAccField
            width:80
            height: 25
            placeholderText: qsTr("Accuracy")
                        validator: IntValidator{}
                    }

                    TextField {
                        id: newAtkField
                        placeholderText: qsTr("Attack")
            width:80
            height: 25
            validator: IntValidator{}
                    }

                    ComboBox {
                        id: dmgTypeCombo
                        model:myCons.damageTypes
                        width:130
                        style:ComboBoxStyle
                        {
                            label:Label
                            {
                                text:(dmgTypeCombo.currentIndex == -1)? "Damage Type" : dmgTypeCombo.currentText + " Damage"
                            }
                        }
                    }

                    TextField {
                        id: newDefField
                        placeholderText: qsTr("Defense")
            width:80
            height: 25
            validator: IntValidator{}
                    }
                    TextField {
                        id: newOverField
                        placeholderText: qsTr("Overwhelming")
            width:80
            height: 25
            validator: IntValidator{}
                    }
                }

            TableView{
                id: weaponsView
                height: 100
                width:weaponsBox.width - 20
                anchors.horizontalCenter: parent.horizontalCenter

                model:ListModel{}
                TableViewColumn {
                    role: "name"
                    title: "Weapon"
                    width: 150
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

    Row {
        id: buttonRow
    x: 338
    width: 160
    anchors.bottom: parent.bottom
    anchors.bottomMargin: 9
    anchors.top: weaponsBox.bottom
    anchors.topMargin: 11
    anchors.rightMargin: 5
    spacing: 10
    anchors.right: parent.right



    Button {
        id: okButton
        text: qsTr("OK")
        enabled: nameField.text.length > 0
        anchors.verticalCenter: parent.verticalCenter
    }
    Button {
        id: cancelButton
        text: qsTr("Cancel")
        anchors.verticalCenter: parent.verticalCenter
    }
}

states:[
        State{
            name: "rangedState"
            when: abilityCombo.currentIndex == 0 || abilityCombo.currentIndex === 4
            PropertyChanges {
                target: rangeCombo
                enabled: true
            }
        },
        State{
            name: "meleeState"
            when: abilityCombo.currentIndex > 0 && abilityCombo.currentIndex < 4
            PropertyChanges {
                target: rangeCombo
                currentIndex: 0
            }
        }
    ]
}



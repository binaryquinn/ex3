import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.2
import Model 1.0




Item {
    id: item2
    width: 580
    height: 525

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

    TextField {
        id: nameField
        anchors.right: armorBox.left
        anchors.rightMargin: 5
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
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
            delegate: Item {
                id:hlDelegate
                x: 5
                width: parent.width
                height: 35
                Row{
                    id: row2
                    spacing: 5

                    Label
                    {
                        id:hlLabel
                        text:penalty
                        anchors.verticalCenter: column1.verticalCenter
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
                        anchors.top: parent.top
                        Button
                        {
                            id: upButton
                            width: 16
                            height: 16
                            iconSource: "images/Up.png"
                            onClicked:
                            {
                                if(hlRepeater.model< 15)
                                {
                                    if(hlRepeater.model>0 &&hlRepeater.model%5 == 0) hlDelegate.height+=21
                                    hlRepeater.model++
                                }
                            }
                        }

                        Button
                        {
                            id: downButton
                            width: 16
                            height: 16
                            iconSource: "images/Down.png"
                            onClicked:
                            {
                                if(hlRepeater.model > 0)
                                {
                                    hlRepeater.model--
                                    if(hlRepeater.model%5 == 0 && hlRepeater.model > 0) hlDelegate.height -= 21
                                }
                            }
                        }
                    }
                    Grid
                    {

                        rows:3
                        columns: 5
                        spacing:5
                        height:parent.height
                        width: 200
                        Repeater
                        {
                            id:hlRepeater
                            model:hlCount
                            Image {
                                id: image1
                                width: 18
                                height: 18
                                source: "images/square-empty.png"
                            }
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
    }

    GroupBox {
        id: weaponsBox
        height: 200
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: healthBox.bottom
        anchors.margins: 5

        title: qsTr("Weapons")
        Column{
            id: weaponLayout
            anchors.rightMargin: 0
            anchors.bottomMargin: -1
            anchors.leftMargin: 0
            anchors.topMargin: 1
            anchors.fill: parent
            spacing: 5

            Column {
                id: newWeaponCol
                width: 200
                height: 50
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 5
                Row {
                    id: weaponTypeRow
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 5
                    TextField {
                        id: newWeaponField
                        placeholderText: qsTr("Weapon Name")
                    }

                    ComboBox {
                        id: abilityCombo
                        model: myCons.combatAbilities
                        width:125
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
                        placeholderText: qsTr("Accuracy")
                        validator: IntValidator{}
                    }

                    TextField {
                        id: newAtkField
                        placeholderText: qsTr("Attack")
                        width:80
                        validator: IntValidator{}
                    }

                    ComboBox {
                        id: dmgTypeCombo
                        model:myCons.damageTypes
                        width:170
                        style:ComboBoxStyle
                        {
                            label:Label
                            {
                                text:(dmgTypeCombo.currentIndex == -1)? "Damage Type" : "Damage Type: "+dmgTypeCombo.currentText
                            }
                        }
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
                }
            }
            TableView{
                id: weaponsView
                height:weaponsBox.height - (newWeaponCol.height + 7 * parent.spacing)

                anchors.margins: 5
                anchors.right: parent.right
                anchors.left: parent.left
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



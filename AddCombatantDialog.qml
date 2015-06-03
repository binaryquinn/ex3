import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Dialogs 1.2
import QtQuick.Controls.Styles 1.2
import QtQuick.Layouts 1.1
import Model 1.0

Dialog
{
    function clearWeapons()
    {
        newWeaponField.text = "";
        qualityCombo.currentIndex = -1;
        weightClassCombo.currentIndex = -1;
        dmgTypeCombo.currentIndex = -1;
        rangeCombo.currentIndex = -1;
        abilityCombo.currentIndex = -1;
    }


    function clearFields()
    {
        nameField.text = "";
        soakField.text = hardnessField.text=  mpField.text = "";

        healthView.model.set(0,{"hlCount":1});
        healthView.model.set(1,{"hlCount":2});
        healthView.model.set(2,{"hlCount":2});
        healthView.model.set(3,{"hlCount":1});
        healthView.model.set(4,{"hlCount":1});

        clearWeapons();
    }

    id:combatantDialog
    title:"Add a new combatant"

    contentItem: Item {
        id: item2
        width: 600
        height: 560



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
        Row{
            Repeater {
                id: attributeRepeater
                model: Tracker.newCombatantAttributes
                delegate:TraitViewDelegate
                {
                id:attributeDelegate
                traitRatingBox.currentIndex: stat - 1
                traitRatingBox.model:[1,2,3,4,5]
            }
        }
    }
}

GroupBox {
    id: abilityBox
    anchors.right: parent.horizontalCenter
    anchors.left: parent.left
    anchors.leftMargin: 5
    anchors.top: healthBox.top
    anchors.bottom: healthBox.bottom

    title: qsTr("Abilities")

    Grid {
        id: abilityGrid
        spacing: 5
        columns: 2

        clip: true
        Repeater {
            id: abilityRepeater
            model:Tracker.newCombatantAbilities
            delegate: TraitViewDelegate
            {
            id:abilityDelegate
            traitRatingBox.currentIndex: stat
            traitRatingBox.model: 6
        }
    }
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
            property int longest: 0
            id: healthView
            interactive: false
            height: parent.height - 5
            delegate:HealthLevelDelegate{
                parentModel:hlModel
                hlLabel.width:healthView.longest
                Component.onCompleted: if(healthView.longest < hlLabel.implicitWidth) healthView.longest = hlLabel.implicitWidth;
            }
            model: ListModel {
                id:hlModel
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
                model: Constants.combatAbilities
                width:120
                style:ComboBoxStyle
                {
                    label:Label
                    {
                        text:(abilityCombo.currentIndex == -1)? "Ability" : abilityCombo.currentText + "-Based"
                    }
                }
                Component.onCompleted: currentIndex = -1
            }
            ComboBox {
                id: rangeCombo
                enabled: false
                width:160
                model:Constants.ranges
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
                enabled: newWeaponField.text.length > 0  && abilityCombo.currentIndex > -1 && qualityCombo.currentIndex > -1 && weightClassCombo.currentIndex > -1 && dmgTypeCombo.currentIndex > -1
                onClicked:
                {
                    var name = newWeaponField.text.trim();

                    if(name.length > 0)
                    {

                        var qual = qualityCombo.currentIndex;
                        var weight = weightClassCombo.currentIndex;
                        var damage = dmgTypeCombo.currentIndex;
                        var range = rangeCombo.currentIndex;
                        var ability = abilityCombo.currentText;

                        Tracker.addWeapon( name,qual,weight,ability,damage,range);

                        clearWeapons();
                    }
                }
            }
        }

        Row {
            id: weaponStatRow
            width: 200
            height: 23
            anchors.left: weaponTypeRow.left
            anchors.leftMargin: 0
            spacing: 5


            ComboBox {
                id: qualityCombo
                model:Weapons.qualities
                width:130
                style:ComboBoxStyle
                {
                    label:Label
                    {
                        text:(qualityCombo.currentIndex == -1)? "Quality" : qualityCombo.currentText + " Quality"
                    }
                }
                Component.onCompleted: currentIndex = -1
            }

            ComboBox {
                id: weightClassCombo
                model:Weapons.weightClasses
                width:130
                style:ComboBoxStyle
                {
                    label:Label
                    {
                        text:(weightClassCombo.currentIndex == -1)? "Weight Class" : weightClassCombo.currentText
                    }
                }
                Component.onCompleted: currentIndex = -1
            }
            ComboBox {
                id: dmgTypeCombo
                model:Constants.damageTypes
                width:130
                style:ComboBoxStyle
                {
                    label:Label
                    {
                        text:(dmgTypeCombo.currentIndex == -1)? "Damage Type" : dmgTypeCombo.currentText + " Damage"
                    }
                }
                Component.onCompleted: currentIndex = -1
            }
        }

        TableView{
            id: weaponsView
            height: 100
            width:weaponsBox.width - 20
            anchors.horizontalCenter: parent.horizontalCenter

            model:Tracker.newCombatantWeapons
            TableViewColumn {
                role: "name"
                title: "Weapon"
                width: 150
            }
            TableViewColumn {
                role: "ability"
                title: "Ability"
                width: 80
            }
            TableViewColumn {
                role: "accuracy"
                title: "Accuracy"
                width: 80
            }
            TableViewColumn {
                role: "damage"
                title: "Damage"
                width: 80
            }
            TableViewColumn {
                role: "overwhelming"
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
        onClicked:
        {
            var soak = (soakField.text !== "")? Number(soakField.text) : 0;
            var hardness = (hardnessField.text !== "")? Number(hardnessField.text) : 0;
            var penalty = (mpField.text !== "")? Number(mpField.text) : 0;
            Tracker.add(nameField.text, soak, hardness, penalty);

            accept();
        }

    }
    Button {
        id: cancelButton
        text: qsTr("Cancel")
        anchors.verticalCenter: parent.verticalCenter
        onClicked:
        {
            reject();
        }
    }
}

states :[
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
}
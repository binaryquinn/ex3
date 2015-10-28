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
        newCombatant.cleanDialog();
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
            anchors.top: parent.top
            anchors.topMargin: 15
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.right: iniField.left
            anchors.rightMargin: 5
            placeholderText: qsTr("Name")
            validator: RegExpValidator
            {
                regExp:/\S+.*/
            }
    }
    TextField{
        id:iniField
        anchors.right: armorBox.left
        anchors.rightMargin: 5
        anchors.top: nameField.top
        width:50
        placeholderText: qsTr("Initiative")
        validator: IntValidator{}
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
            top: iniField.bottom
            topMargin: 5
            right:iniField.right
        }

        title: qsTr("Attributes")
        RowLayout{
            Repeater {
                id: attributeRepeater
                property int longest: 0
                model: newCombatant.attributes

                delegate:TraitViewDelegate
                {
                    id:attributeDelegate
                    traitRatingBox.currentIndex: stat - 1
                    traitRatingBox.model:[1,2,3,4,5]
                    traitLabel.width:attributeRepeater.longest
                    Component.onCompleted: if(attributeRepeater.longest < traitLabel.implicitWidth) attributeRepeater.longest = traitLabel.implicitWidth;
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

        GridLayout {
            anchors.fill: parent
            id: abilityGrid
            columnSpacing: 5
            columns: 2
           Repeater {
               property int longest: 0
                id: abilityRepeater
                model:newCombatant.abilities
                delegate: TraitViewDelegate
                {
                    id:abilityDelegate
                    traitRatingBox.currentIndex: stat
                    traitRatingBox.model: 6
                    traitLabel.width:abilityRepeater.longest
                    Component.onCompleted: if(abilityRepeater.longest < traitLabel.implicitWidth) abilityRepeater.longest = traitLabel.implicitWidth;
                }
            }
        }
    }

    GroupBox
    {
        id:healthBox
        height: 3 * item2.height/8
        title: "Health Levels"
        anchors.left: parent.horizontalCenter
        anchors.right: parent.right

        anchors.top: armorBox.bottom
        anchors.margins: 10

    ScrollView{
            anchors.fill: parent

            ListView {
                property int longest: 0
                id: healthView
                interactive: false
                delegate:HealthLevelDelegate{
                    parentModel:newCombatant.healthLevels
                    hlLabel.width:healthView.longest
                    Component.onCompleted: if(healthView.longest < hlLabel.implicitWidth) healthView.longest = hlLabel.implicitWidth;
                }
                model:newCombatant.healthLevels
            }
        }
    }

    GroupBox {
        id: weaponsBox

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: healthBox.bottom

    anchors.bottom: buttonRow.top
    anchors.margins: 10


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
                        var damage = dmgTypeCombo.currentIndex+1;
                        var range = rangeCombo.currentIndex;
                        var ability = abilityCombo.currentText;

                        newCombatant.addWeapon( name,qual,weight,ability,damage,range);

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
            height: weaponsBox.height - (weaponStatRow.y + weaponStatRow.height + (2 * (weaponLayout.spacing + weaponsBox.anchors.margins)))
            width:weaponsBox.width - 20
            anchors.horizontalCenter: parent.horizontalCenter

            model:newCombatant.weapons
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

    anchors.bottom: parent.bottom
    anchors.bottomMargin: 10
    anchors.rightMargin: 10
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
            var ini = (iniField.text !=="")? Number(iniField.text): undefined;
            newCombatant.makeCombatant(nameField.text, ini, soak, hardness, penalty);
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
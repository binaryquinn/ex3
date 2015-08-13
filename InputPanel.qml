import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.2
import Model 1.0


Item{

    height: 50

    readonly property int initiativeDamage: initiativeAmountSpinner.value*((initiativeVerbCombo.currentIndex < 1)?1:-1)
    readonly property int healthDamage: healthAmountSpinner.value*((healthVerbCombo.currentIndex < 1)?1:-1)
    property alias woundUnit: woundTypeCombo.currentIndex

    Column {
        id: columnLayout1
        anchors.fill: parent

        Row{
            id: rowLayout1
            spacing: 5

            ComboBox {
                id: initiativeVerbCombo
                model: Constants.verbs
                width:75
            }

            SpinBox {
                id: initiativeAmountSpinner
                width: 50
                minimumValue: 0
                value: 0
            }
             Label{
              text:"Initiative"
             }
            }

        Row {
            id: rowLayout2
            spacing: 5

            ComboBox {
                id: healthVerbCombo
                model: Constants.verbs
                width:75
                currentIndex: model.length-1
            }

            SpinBox {
                id: healthAmountSpinner
                width: 50
                minimumValue: 0
                value: 0
            }

            ComboBox {
                id: woundTypeCombo
                model: Constants.damageTypes
                width:90
            }

            Label{
             text:"Health Levels"
            }
        }
    }

}


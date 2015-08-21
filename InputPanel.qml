import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.2
import Model 1.0

Item{
    height: woundTypeCombo.height*3
    width:300
    readonly property int initiativeDamage: initiativeAmountSpinner.value*((initiativeVerbCombo.currentIndex < 1)?1:-1)
    readonly property int healthDamage: healthAmountSpinner.value*((healthVerbCombo.currentIndex < 1)?1:-1)
    property alias woundUnit: woundTypeCombo.currentIndex


    ColumnLayout{
        anchors.fill: parent
        anchors.margins: 5
        spacing: 5
        RowLayout{
            height:(parent.height-parent.spacing-parent.anchors.margins)/2
            spacing: 5
            ComboBox {
                id: initiativeVerbCombo
                model: Constants.verbs
                Layout.preferredWidth: 65
                Layout.fillWidth:false
            }

            SpinBox {
                id: initiativeAmountSpinner
                minimumValue: 0
                value: 0
                Layout.fillWidth:false
            }
            Label{
                text:"Initiative"

            }
        }
        RowLayout{
            height:(parent.height-parent.spacing-parent.anchors.margins)/2
            ComboBox {
                id: healthVerbCombo
                model: Constants.verbs
                Layout.preferredWidth:65
                Layout.fillWidth:false
            }

            SpinBox {
                id: healthAmountSpinner
                minimumValue: 0
                value: 0
                Layout.fillWidth:false


            }

            ComboBox {
                id: woundTypeCombo
                model: Constants.damageTypes
                Layout.preferredWidth: 100
                Layout.fillWidth:false
            }

            Label{
                text:"Health Levels"
            }
        }
    }
}


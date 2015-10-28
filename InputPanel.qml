import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.2
import Model 1.0

Item{
    height: woundTypeCombo.height*3
    width: 275
    readonly property int initiativeDamage: initiativeAmountSpinner.value*((initiativeVerbCombo.currentIndex < 1)?1:-1)
    readonly property int healthDamage: healthAmountSpinner.value
    property alias woundUnit: woundTypeCombo.currentIndex

    GridLayout{
        anchors.fill: parent
        anchors.margins: 5
        columns: 3
            ComboBox {
                id: initiativeVerbCombo
                model: Constants.verbs
                Layout.preferredWidth: 70
                Layout.fillWidth:false
                Layout.alignment:Qt.AlignRight
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
            Label{
                text:"Takes"
                Layout.alignment:Qt.AlignRight
            }

            SpinBox {
                id: healthAmountSpinner
                minimumValue: 0
                value: 0
            }

            ComboBox {
                id: woundTypeCombo
                enabled: healthAmountSpinner.value > 0
                model: Constants.damageTypes
                Layout.preferredWidth: 130
                Layout.fillWidth:false
                style:ComboBoxStyle {
                    label:Label {
                        text:(woundTypeCombo.currentIndex == -1)? "Damage Type":woundTypeCombo.currentText + " Damage"
                    }
                }
                currentIndex: -1
            }
        }
    }



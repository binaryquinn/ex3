import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Extras 1.4
import QtQuick.Layouts 1.2

Item {

    id: rectangle1

    property alias text:basePoolLabel.text
    property int base: 0
    property int penalty: 0
    QtObject{
        id:finalProp
        property int finalValue: (base > penalty)?(base - penalty):0;

    }

    signal result( bool method, int value);
    Item {
        id: poolBox
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        //anchors.bottom: resultsPanel.top
        anchors.bottomMargin: 5
        anchors.top: parent.top
        anchors.topMargin: 0
        Label{
            id:basePoolLabel
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0


        }
        Label{
            id:penaltyLabel
            anchors.top: basePoolLabel.bottom
            anchors.topMargin: 5
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            text: "penaltys: " + penalty
        }

        Label{
            id:finalPoolLabel
            anchors.top: penaltyLabel.bottom
            anchors.topMargin: 5
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            text: "Final Pool: " + finalProp.finalValue
        }
    }
//    Item{
//        id: resultsPanel
//        height: 50
//        anchors.bottom: parent.bottom
//        anchors.bottomMargin: 0
//        anchors.right: parent.right
//        anchors.rightMargin: 0
//        anchors.left: parent.left
//        anchors.leftMargin: 0
//        Item {
//            id: switchPanel

//        width: 20
//        height: 50
//        anchors.verticalCenter: parent.verticalCenter
//        anchors.left: parent.left

//        Switch {
//            id: rollSwitch
//            width: 48
//            height: 20
//            anchors.centerIn: parent
//            rotation: -90
//            checked:true

//        }
//    }

//    Label {
//        id: enterYourResultsLabel

//        text:qsTr("Enter your own results")
//        anchors.verticalCenterOffset: parent.height/-4
//        anchors.verticalCenter: parent.verticalCenter
//        anchors.left: switchPanel.right
//        anchors.leftMargin: 5
//    }

//    SpinBox {
//        id: yourResultsSpinner
//        width: 50
//        anchors.verticalCenter: enterYourResultsLabel.verticalCenter
//        anchors.left: enterYourResultsLabel.right
//        anchors.leftMargin: 10
//        enabled: rollSwitch.checked
//    }

//    Label {
//        id: forYouLabel

//        text:qsTr("Roll the above values for you")
//        anchors.verticalCenter: parent.verticalCenter
//        anchors.verticalCenterOffset: parent.height/4
//        anchors.left: switchPanel.right
//        anchors.leftMargin: 5
//    }

//    Button {
//        id: commitButton
//        width: height
//        text: qsTr("Go!")
//        anchors.bottom: parent.bottom
//        anchors.bottomMargin: 5
//        anchors.top: parent.top
//        anchors.topMargin: 5
//        anchors.right: parent.right
//        anchors.rightMargin: 5
//        onClicked: {
//            (rollSwitch.checked )? result(rollSwitch.checked,yourResultsSpinner.value): result(rollSwitch.checked, finalProp.finalValue);
//        }
//    }
//}


}


import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Extras 1.4
import QtQuick.Layouts 1.2
import QtQuick.Controls.Styles 1.2

Item {

    id: rectangle1

    property alias text:basePoolLabel.text
    property int base: 0
    property int penalty: 0
    QtObject{
        id:finalProp
        property int finalValue: (base > penalty)?(base - penalty):0;

    }
    Item {
        id: poolBox
        anchors.fill: parent
        anchors.margins: 5
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
}

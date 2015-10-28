import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Extras 1.4
import QtQuick.Layouts 1.2
import QtQuick.Controls.Styles 1.2

Item {

    id: resultsPanel
    height: 75
    width: (yourResultsLabel.implicitWidth > forYouLabel.implicitWidth?
            yourResultsLabel.implicitWidth : forYouLabel.implicitWidth)
           + switchPanel.width + 15
    anchors.bottom: parent.bottom
    anchors.bottomMargin: 0

    readonly property alias checked:rollSwitch.checked

    Item {
        id: switchPanel

        width: 30
        height: parent.height
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left

        Switch {
            id: rollSwitch
            width: parent.height-10
            height:30
            style: SwitchStyle {
                groove: Rectangle {
                    implicitWidth: control.width
                    implicitHeight: control.height
                    radius: 5
                    color: "gray"
                    border.width: 1
                }
                handle: Rectangle {
                    implicitWidth: control.width/2
                    implicitHeight: control.height
                    radius: 5
                    border.width: 1
                }
            }
            anchors.centerIn: parent
            rotation: -90
            checked:true

        }
    }

    Label {
        id: yourResultsLabel

        text:qsTr("Use your own results")
        anchors.verticalCenterOffset: parent.height/-4
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: switchPanel.right
        anchors.leftMargin: 5
    }
    Label {
        id: forYouLabel

        text:qsTr("Roll for you")
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: parent.height/4
        anchors.left: switchPanel.right
        anchors.leftMargin: 5
    }
}


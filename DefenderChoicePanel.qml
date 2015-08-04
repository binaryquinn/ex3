import QtQuick 2.4
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.2
import Model 1.0


Item{

    property alias model: defensesView.model
    property alias choice: defensesView.currentIndex

    id:defPanel
    width: 300
    height: 300

    ColumnLayout {
        id: columnLayout1
        anchors.fill: parent

        Label {
            id: infoLabel
            text: qsTr("Select defender's method of defense from the list below")
            anchors.horizontalCenter: parent.horizontalCenter
        }
        GroupBox{

            anchors.top:infoLabel.bottom
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.left: parent.left
            anchors.leftMargin: 20
           // anchors.bottom:buttonRow.top
            title: qsTr("Defenses")
            ScrollView
            {
                id:defenseScroll
                anchors.fill: parent
                anchors.margins: 5
                ListView {
                    id: defensesView
                    x: 95
                    y: 149
                    anchors.fill: parent
                    delegate: Item{
                        x: 5
                        width: parent.width
                        height: 40
                        MouseArea{
                            anchors.fill: parent
                            onClicked: {
                                defensesView.currentIndex = index;
                            }
                            Label{
                                text: modelData
                                font.bold: true
                                anchors.verticalCenter: parent.verticalCenter
                            }
                        }
                    }
                    model: 0;
                    onModelChanged: currentIndex = -1;
                    //highlight: highlightBar
                    Component.onCompleted: currentIndex = -1
                }
            }
        }
    }
}
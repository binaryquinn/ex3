import QtQuick 2.4
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.2
import Model 1.0

Dialog
{

    property alias model: defensesView.model
    property alias choice: defensesView.currentIndex
contentItem:Item{
    id:defDialog
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
            anchors.bottom:buttonRow.top
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
                    highlight: highlightBar
                    Component.onCompleted: currentIndex = -1
                }
            }
        }
        Row {
            id: buttonRow
            x: 338
            width: 160
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 9

            height:40
            anchors.rightMargin: 5
            spacing: 10
            anchors.right: parent.right

            Button {
                id: okButton
                text: qsTr("OK")
                enabled: defensesView.currentIndex > -1
                anchors.verticalCenter: parent.verticalCenter
                onClicked:
                {
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
    }
}
    onVisibleChanged: if(visible)choice = -1;
}
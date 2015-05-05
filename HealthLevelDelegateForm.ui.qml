import QtQuick 2.4
import QtQuick.Controls 1.3

Item {
    property alias hlColumn:hlColumn
    property alias hlRepeater: hlRepeater

    id:hlDelegate
    x: 5
    height: 35
    Row{
        id: row2
        spacing: 5

        Label
        {
            id:hlLabel
            text:penalty
            anchors.verticalCenter: hlColumn.verticalCenter
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
            width:longest
            Component.onCompleted: if(longest < implicitWidth) longest = implicitWidth;

        }
        UpDownColumn
        {
            id:hlColumn
        }
        Grid
        {

            rows:3
            columns: 5
            spacing:5
            height:parent.height
            width: 200
            Repeater
            {
                id:hlRepeater
                model:hlCount
                Image {
                    id: image1
                    width: 18
                    height: 18
                    source: "images/square-empty.png"
                }
            }
        }
    }
}



import QtQuick 2.4

import QtQuick 2.4
import QtQuick.Controls 1.3


Column
{
    signal up()
    signal down()

    id: column1
    width: 16
    height: 32
    spacing: 0
    anchors.top: parent.top
    Button
    {
        id: upButton
        width: 16
        height: 16
        iconSource: "images/Up.png"
        onClicked: up();
    }

    Button
    {
        id: downButton
        width: 16
        height: 16
        iconSource: "images/Down.png"
        onClicked: down();
    }
}









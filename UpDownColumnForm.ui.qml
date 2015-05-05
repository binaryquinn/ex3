import QtQuick 2.4
import QtQuick.Controls 1.3


Column
{
    property alias upButton: upButton
    property alias downButton: downButton
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
//        onClicked:
//        {
//            if(hlRepeater.model< 15)
//            {
//                if(hlRepeater.model>0 &&hlRepeater.model%5 == 0) hlDelegate.height+=21
//                hlRepeater.model++
//            }
//        }
    }

    Button
    {
        id: downButton
        width: 16
        height: 16
        iconSource: "images/Down.png"
//        onClicked:
//        {
//            if(hlRepeater.model > 0)
//            {
//                hlRepeater.model--
//                if(hlRepeater.model%5 == 0 && hlRepeater.model > 0) hlDelegate.height -= 21
//            }
//        }
    }
}

import QtQuick 2.4
import QtQuick.Controls 1.3


    Item {

        property var parentModel;
        property alias hlLabel:hlLabel

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

            }
            UpDownColumn
            {
                id:hlColumn
                onUp:
                    {
                        if(hlRepeater.model< 15)
                        {
                            if(hlRepeater.model>0 &&hlRepeater.model%5 == 0) hlDelegate.height+=21
                            parentModel.set(index, {"hlCount":hlRepeater.model+1});
                        }
                    }
                onDown:
                    {
                        if(hlRepeater.model > 0)
                        {
                            parentModel.set(index, {"hlCount":hlRepeater.model-1});
                            if(hlRepeater.model%5 == 0 && hlRepeater.model > 0) hlDelegate.height -= 21
                        }
                    }
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
                    onModelChanged: if(model < 3) hlDelegate.height = 35
                }
            }
        }
    }



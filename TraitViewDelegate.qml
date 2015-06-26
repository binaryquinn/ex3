import QtQuick 2.4
import QtQuick.Controls 1.3

Item {
    width: 100
    height: 30
    property alias traitLabel: traitLabel
    property alias traitRatingBox: traitRatingBox
    Row {
        id: row1
        spacing: 5
        Label {
            id: traitLabel
            width: 59
            height: 20
            text: name + ":"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignRight
        }

        ComboBox {
            id: traitRatingBox
            width: 40
            height: 20
            onActivated:
            {
                stat = parseInt(textAt(index));
            }
        }
    }
}





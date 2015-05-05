import QtQuick 2.4


UpDownColumnForm {
    signal up()
    signal down()

    upButton.onClicked: up();
    downButton.onClicked: down();

}


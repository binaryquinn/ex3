import QtQuick 2.4
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.0

Item {
	id: item1
	width: 600
	height: 250

	Label {
		id: nameLabel
		text: qsTr("")
		anchors.right: parent.right
  anchors.rightMargin: 10
  anchors.left: parent.left
		anchors.leftMargin: 10
		anchors.top: parent.top
		anchors.topMargin: 10
	}

	Label {
		id: initiativeLabel
		text: qsTr("Initiave:")
		anchors.top: nameLabel.bottom
		anchors.topMargin: 5
		anchors.left: parent.left
		anchors.leftMargin: 10
	}

	Label {
		id: nSoakLabel
		text: qsTr("Natural Soak:")
		anchors.top: initiativeLabel.bottom
		anchors.topMargin: 5
		anchors.left: parent.left
		anchors.leftMargin: 10
	}

	Label {
		id: aSoakLabel
		x: 111
		text: qsTr("Armor Soak:")
		anchors.top: nSoakLabel.top
		anchors.topMargin: 0
	}

	Label {
		id: totalSoakLabel
		x: 220
		text: qsTr("Total Soak:")
		anchors.top: nSoakLabel.top
		anchors.topMargin: 0
	}

	Label {
		id: doWhatLabel
		x: 28
		y: 150
		text: qsTr("Do What?")
		anchors.bottom: rectangle1.top
		anchors.bottomMargin: 5
		anchors.horizontalCenter: rectangle1.horizontalCenter
	}

	ScrollView {
		id: rectangle1
		width: (item1.width/3)-40
		anchors.bottom: parent.bottom
		anchors.bottomMargin: 10
		anchors.top: parent.verticalCenter
		anchors.topMargin: 0
		anchors.left: parent.left
		anchors.leftMargin: 10

		ListView {
			id: listView1
			anchors.fill: parent
			delegate: Item {
				x: 5
				width: 80
				height: 40
				Row {
					id: row1
					spacing: 10
					Rectangle {
						width: 40
						height: 40
						color: colorCode
					}

					Text {
						text: name
						font.bold: true
						anchors.verticalCenter: parent.verticalCenter
					}
				}
			}
			model: ListModel {
				ListElement {
					name: "Grey"
					colorCode: "grey"
				}

				ListElement {
					name: "Red"
					colorCode: "red"
				}

				ListElement {
					name: "Blue"
					colorCode: "blue"
				}

				ListElement {
					name: "Green"
					colorCode: "green"
				}
			}
		}
	}

	ScrollView{
		id: rectangle2
		x: 138
		width: rectangle1.width
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.bottom: parent.bottom
		anchors.bottomMargin: 10
		anchors.top: parent.verticalCenter
		anchors.topMargin: 0

		ListView {
			id: listView2
			anchors.fill: parent
			delegate: Item {
		  x: 5
		  width: 80
		  height: 40
		  Row {
			  id: row2
			  spacing: 10
			  Rectangle {
				  width: 40
				  height: 40
				  color: colorCode
			  }

			  Text {
				  text: name
				  font.bold: true
				  anchors.verticalCenter: parent.verticalCenter
			  }
		  }
	  }
	  model: ListModel {
		  ListElement {
			  name: "Grey"
			  colorCode: "grey"
		  }

		  ListElement {
			  name: "Red"
			  colorCode: "red"
		  }

		  ListElement {
			  name: "Blue"
			  colorCode: "blue"
		  }

		  ListElement {
			  name: "Green"
			  colorCode: "green"
		  }
	  }
  }
	}

	ScrollView {
		id: rectangle3
		x: 272
		width: rectangle1.width
		anchors.right: parent.right
		anchors.rightMargin: 10
		anchors.bottom: parent.bottom
		anchors.bottomMargin: 10
  anchors.top: parent.verticalCenter
		anchors.topMargin: 0

		ListView {
			id: listView3
			anchors.fill: parent
	  delegate: Item {
		  x: 5
		  width: 80
		  height: 40
		  Row {
			  id: row3
			  spacing: 10
			  Rectangle {
				  width: 40
				  height: 40
				  color: colorCode
			  }

			  Text {
				  text: name
				  font.bold: true
				  anchors.verticalCenter: parent.verticalCenter
			  }
		  }
	  }
	  model: ListModel {
		  ListElement {
			  name: "Grey"
			  colorCode: "grey"
		  }

		  ListElement {
			  name: "Red"
			  colorCode: "red"
		  }

		  ListElement {
			  name: "Blue"
			  colorCode: "blue"
		  }

		  ListElement {
			  name: "Green"
			  colorCode: "green"
		  }
	  }
  }
 }

 Label {
	 id: toWhomLabel
	 x: 169
	 y: 150
	 text: qsTr("To Whom?")
	 anchors.bottom: rectangle2.top
	 anchors.bottomMargin: 5
	 anchors.horizontalCenter: rectangle2.horizontalCenter
 }

 Label {
	 id: withWhatlabel
	 x: 299
	 y: 150
	 text: qsTr("With What?")
	 anchors.bottom: rectangle3.top
	 anchors.bottomMargin: 5
	 anchors.horizontalCenter: rectangle3.horizontalCenter
 }
}


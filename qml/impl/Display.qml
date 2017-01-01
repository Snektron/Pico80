import QtQuick 2.0

Rectangle {
	color: "#C0C0C0"
	anchors.margins: 10

	Column {
		anchors.centerIn: parent
		Text {
			color: "#101010"
			text: "\uF071"
			font.pointSize: 50
			font.family: "FontAwesome"
			anchors.horizontalCenter: parent.horizontalCenter
		}

		Text {
			color: "#101010"
			width: parent.parent.width
			horizontalAlignment: Text.AlignHCenter
			text: "No plugin selected or something has gone wrong."
			font.pointSize: 10
			font.family: "Roboto"
			wrapMode: Text.WordWrap
			anchors.horizontalCenter: parent.horizontalCenter
		}
	}
}

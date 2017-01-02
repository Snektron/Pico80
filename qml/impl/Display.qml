import QtQuick 2.0

Rectangle {
	color: "#D0D0D0"

	Column {
		anchors.centerIn: parent
		Text {
			color: "#7F7F7F"
			text: "\uF071"
			font.pointSize: 50
			font.family: "FontAwesome"
			anchors.horizontalCenter: parent.horizontalCenter
		}

		Text {
			color: "#7F7F7F"
			width: parent.parent.width
			horizontalAlignment: Text.AlignHCenter
			text: "No plugin selected or something has gone wrong."
			font.pointSize: 10
			font.family: "OpenSans"
			wrapMode: Text.WordWrap
			anchors.horizontalCenter: parent.horizontalCenter
		}
	}
}

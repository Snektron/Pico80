import QtQuick 2.0
import Pico80.Components 1.0

View {
	id: display
	color: theme.display_placeholder.background

	Column {
		anchors.centerIn: parent

		Text {
			color: theme.display_placeholder.text
			text: "\uF071"
			font.pointSize: 50
			font.family: "FontAwesome"
			anchors.horizontalCenter: parent.horizontalCenter
		}

		Text {
			color: theme.display_placeholder.text
			width: display.width
			horizontalAlignment: Text.AlignHCenter
			text: "No plugin selected or something has gone wrong."
			font.pointSize: 10
			font.family: "Roboto Light"
			wrapMode: Text.WordWrap
			anchors.horizontalCenter: parent.horizontalCenter
		}
	}
}

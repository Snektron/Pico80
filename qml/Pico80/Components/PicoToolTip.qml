import QtQuick 2.0
import QtQuick.Controls 2.0
import QtGraphicalEffects 1.0

Popup {
	id: popup

	property alias text: text.text
	property alias textColor: text.color
	property alias bgColor: rect.color
	property alias shadowColor: background.color

	background: RectangularGlow {
		id: background
		glowRadius: 1
		spread: 0.2
		color: theme.tooltip.shadow
		cornerRadius: 6
		width: text.width + 10
		height: text.height + 10
		x: -width / 2

		Rectangle {
			id: rect
			anchors.fill: parent
			radius: 4
			color: theme.tooltip.background
		}
	}

	contentItem: Text {
		id: text
		text: "tooltip"
		anchors.centerIn: background
		color: theme.tooltip.text
		font.family: "Roboto"
		font.pointSize: 10
	}
}

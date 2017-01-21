import QtQuick 2.5
import QtQuick.Controls 2.0

Button {
	id: control
	implicitHeight: 15
	font.pointSize: 10
	font.family: "Roboto Light"
	hoverEnabled: true

	property color pressedColor: Theme.button.pressed
	property color releasedColor: Theme.button.primary
	property color hoveredColor: Theme.button.hovered
	property alias tooltip: tooltiparea.tooltip

	contentItem: Text {
		font: control.font
		text: control.text
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.verticalCenter: parent.verticalCenter
		verticalAlignment: Text.AlignVCenter
		horizontalAlignment: Text.AlignHCenter
	}

	background: Rectangle {
		id: background
		implicitHeight: parent.implicitHeight
		color: pressed ? pressedColor :
			   hovered ? hoveredColor :
			   releasedColor
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.verticalCenter: parent.verticalCenter
		visible: !flat || pressed || hovered
	}

	PicoToolTipArea {
		id: tooltiparea
		anchors.fill: parent
	}
}

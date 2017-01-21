import QtQuick 2.5
import QtQuick.Controls 2.0

CheckBox {
	id: control
	implicitWidth: 24
	implicitHeight: 24
	font.pixelSize: 14
	font.family: "FontAwesome"
	hoverEnabled: true

	property color enabledColor: Theme.toolbar.button.checked
	property color disabledColor: Theme.toolbar.button.unchecked
	property color hoveredColor: Theme.toolbar.button.hovered
	property alias tooltip: tooltiparea.tooltip

	indicator: Rectangle {
		implicitWidth: parent.implicitWidth
		implicitHeight: parent.implicitHeight
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.verticalCenter: parent.verticalCenter
		color: hovered ? hoveredColor : "#00000000"
		radius: 2

		Text {
			id: indicatorText
			anchors.verticalCenter: parent.verticalCenter
			anchors.horizontalCenter: parent.horizontalCenter
			text: control.text
			font: control.font
			color: checked ? enabledColor : disabledColor
		}
	}

	contentItem: Item {}

	PicoToolTipArea {
		id: tooltiparea
		anchors.fill: parent
	}
}

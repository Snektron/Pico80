import QtQuick 2.5
import QtQuick.Controls 2.0

Button {
	id: control
	implicitHeight: 24
	implicitWidth: 24
	font.pointSize: 14
	font.family: "FontAwesome"
	hoverEnabled: true

	property color pressedColor: theme.toolbar.button.pressed
	property color hoveredColor: theme.toolbar.button.hovered
	property alias tooltip: tooltiparea.tooltip
	property alias tooltiparea: tooltiparea

	contentItem: Text {
		font: control.font
		text: control.text
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.verticalCenter: parent.verticalCenter
		verticalAlignment: Text.AlignVCenter
		horizontalAlignment: Text.AlignHCenter
	}

	background: Rectangle {
		radius: 2
		id: background
		implicitHeight: parent.implicitHeight
		implicitWidth: parent.implicitWidth
		color: pressed ? pressedColor : hoveredColor
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.verticalCenter: parent.verticalCenter
		visible: pressed || hovered
	}

	PicoToolTipArea {
		id: tooltiparea
		anchors.fill: parent
	}
}

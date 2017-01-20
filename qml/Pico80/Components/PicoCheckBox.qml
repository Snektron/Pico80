import QtQuick 2.5
import QtQuick.Controls 2.0

CheckBox {
	id: control
	implicitHeight: 15
	spacing: 3
	font.pointSize: 10
	font.family: "Roboto Light"

	property alias checkSize: indicatorText.font.pointSize
	property alias tooltip: tooltiparea.tooltip
	property alias bgColor: indicator.color

	indicator: Rectangle {
		id: indicator
		implicitWidth: 15
		implicitHeight: 15
		anchors.verticalCenter: parent.verticalCenter

		color: theme.checkbox.background

		Text {
			id: indicatorText
			anchors.verticalCenter: parent.verticalCenter
			anchors.horizontalCenter: parent.horizontalCenter
			visible: control.checked
			text: "\uF00C"
			font.pointSize: 10
			font.family: "FontAwesome"
		}
	}

	contentItem: Text {
		id: text
		text: control.text
		font: control.font
		anchors.left: indicator.right
		anchors.leftMargin: parent.spacing
		anchors.verticalCenter: parent.verticalCenter
		horizontalAlignment: Text.AlignHCenter
		verticalAlignment: Text.AlignVCenter
	}

	PicoToolTipArea {
		id: tooltiparea
		anchors.fill: parent
	}
}

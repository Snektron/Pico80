import QtQuick 2.5
import QtQuick.Controls 2.0

ComboBox {
	id: control
	implicitHeight: 15
	font.family: "Roboto Light"
	spacing: 3

	property alias tooltip: tooltiparea.tooltip

	indicator: Text {
		id: indicator
		anchors.right: parent.right
		anchors.rightMargin: 3
		anchors.verticalCenter: parent.verticalCenter
		text: "\uF107"
		font.pointSize: 10
		font.family: "FontAwesome"
	}

	delegate: ItemDelegate {
		width: control.width
		implicitHeight: 15
		highlighted: control.highlightedIndex == index

		contentItem: Text {
			text: modelData
			font: control.font
			elide: Text.ElideRight
			verticalAlignment: Text.AlignVCenter
			anchors.verticalCenter: parent.verticalCenter
			anchors.left: parent.left
			anchors.leftMargin: control.spacing
		}
	}

	contentItem: Text {
		id: text
		text: control.currentText
		font: control.font
		anchors.verticalCenter: control.verticalCenter
		verticalAlignment: Text.AlignVCenter
		anchors.right: indicator.left
		anchors.left: control.left
		anchors.leftMargin: control.spacing
	}

	PicoToolTipArea {
		id: tooltiparea
		anchors.fill: parent
	}
}

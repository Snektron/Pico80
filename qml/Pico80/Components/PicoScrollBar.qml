import QtQuick 2.5
import QtQuick.Controls 2.0

ScrollBar {
	id: bar
	implicitWidth: 12

	contentItem: Rectangle {
		color: bar.pressed ? Theme.scrollbar.grabbed : Theme.scrollbar.slider
		anchors.left: parent.left
		anchors.right: parent.right
		anchors.margins: 1
		height: parent.height * bar.size
		y: parent.height * bar.position
	}

	background: Rectangle {
		id: background
		anchors.fill: parent
		color: Theme.scrollbar.background
	}
}

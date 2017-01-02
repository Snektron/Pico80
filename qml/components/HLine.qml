import QtQuick 2.0

Item {
	property alias color: line.color
	property alias lineHeight: line.height
	property real lineScale: 1

	height: 10
	anchors.left: parent.left
	anchors.right: parent.right

	Rectangle {
		id: line
		anchors.centerIn: parent
		height: 1
		width: parent.width * lineScale
		color: "#101010"
	}
}

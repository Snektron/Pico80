import QtQuick 2.0

Rectangle {
	color: "#FFFFFF"
	anchors.fill: parent
	anchors.topMargin: toolbar.height

	property alias toolbar: toolbar.items

	PicoToolBar {
		id: toolbar
		y: -height
	}
}

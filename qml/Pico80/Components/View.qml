import QtQuick 2.0

Rectangle {
	color: "#FFFFFF"
	anchors.fill: parent
	anchors.topMargin: toolbar.height

	property string icon: "\uF2DB"
	property string caption: "View"
	property alias toolbar: toolbar.items

	signal show()

	PicoToolBar {
		id: toolbar
		y: -height
	}
}

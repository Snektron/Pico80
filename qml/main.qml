import QtQuick 2.5
import QtQuick.Window 2.2

Window {
	id: window
    visible: true
	width: 800
	height: 600
	title: "Pico80"
	minimumWidth: 64+10+300+10+200+10

    MainForm {
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        anchors.left: parent.left
    }
}

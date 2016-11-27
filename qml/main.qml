import QtQuick 2.5
import QtQuick.Window 2.2

Window {
    id: window1
    visible: true
    width: 640
    height: 480
	title: qsTr("Pico-80")

    MainForm {
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        anchors.left: parent.left
    }
}

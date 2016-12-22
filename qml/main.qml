import QtQuick 2.5
import QtQuick.Window 2.2

Window {
    visible: true
	width: 800
	height: 600
	title: "Pico80"
	minimumWidth: 80 + 300 + 1 + 250
	minimumHeight: 400

    MainForm {
		anchors.fill: parent
    }
}

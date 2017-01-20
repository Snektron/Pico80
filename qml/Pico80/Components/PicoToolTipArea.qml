import QtQuick 2.0

MouseArea {
	hoverEnabled: true
	acceptedButtons: Qt.NoButton

	property alias tooltip: tooltiploader.sourceComponent
	property alias delay: timer.interval

	onEntered: timer.restart()
	onExited: {
		tooltiploader.close()
		timer.stop()
	}

	Loader {
		id: tooltiploader
		anchors.top: parent.bottom
		anchors.horizontalCenter: parent.horizontalCenter

		function open() {
			if (item)
				item.open()
		}

		function close() {
			if (item)
				 item.close()
		}
	}

	Timer {
		id: timer
		repeat: false
		running: false
		interval: 1000
		onTriggered: tooltiploader.open()
	}
}

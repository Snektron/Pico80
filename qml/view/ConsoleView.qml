import QtQuick 2.5
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import Pico80.Components 1.0

View {
	toolbar: Row {
		spacing: 2
		anchors.leftMargin: 4
		anchors.fill: parent

		PicoToolButton {
			id: clearButton
			text: "\uF12D"
			anchors.verticalCenter: parent.verticalCenter
			onClicked: pico.logModel.clear()

			tooltip: PicoToolTip {
				text: "Clear console"
			}
		}

		PicoToolCheckBox {
			id: autoscroll
			text: "\uF07d"
			anchors.verticalCenter: parent.verticalCenter

			checked: settings.autoscroll;
			onCheckedChanged: settings.autoscroll = checked;

			tooltip: PicoToolTip {
				text: "Enable autoscrolling"
			}
		}
	}

	Rectangle {
		color: Theme.console.background
		anchors.fill: parent

		ListView {
			id: logview
			boundsBehavior: Flickable.StopAtBounds
			flickableDirection: Flickable.VerticalFlick
			anchors.fill: parent

			property var consolecolors: [
				Theme.console.log.debug,
				Theme.console.log.warning,
				Theme.console.log.critical,
				Theme.console.log.fatal,
				Theme.console.log.info
			]

			model: Pico.logModel

			onCountChanged: {
				if (settings.autoscroll) {
					positionViewAtEnd();
					currentIndex = count - 1;
				}
			}

			delegate: Text {
				text: record
				color: logview.consolecolors[type]
				anchors.left: parent.left
				anchors.right: parent.right
				anchors.leftMargin: 5
				anchors.rightMargin: 5 + scrollbar.width
				textFormat: Text.PlainText
				wrapMode: Text.WordWrap
				font.pointSize: 11
				font.family: "Courier"
			}

			ScrollBar.vertical: PicoScrollBar {
				id: scrollbar
			}
		}
	}
}

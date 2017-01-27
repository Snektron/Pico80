import QtQuick 2.5
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import Pico80.Components 1.0

View {
	icon: "\uF120"
	caption: "Console"
	color: Theme.console.background

	toolbar: Row {
		spacing: 2
		anchors.leftMargin: 4
		anchors.fill: parent

		PicoToolButton {
			id: clearButton
			text: "\uF12D"
			anchors.verticalCenter: parent.verticalCenter
			onClicked: Pico.logModel.clear()

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

	ColumnLayout {
		anchors.fill: parent
		spacing: 0

		ListView {
			id: logview
			boundsBehavior: Flickable.StopAtBounds
			flickableDirection: Flickable.VerticalFlick
			Layout.fillWidth: true
			Layout.fillHeight: true

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
				font.pixelSize: 13
				font.family: "Courier"
				renderType: Text.NativeRendering
			}

			ScrollBar.vertical: PicoScrollBar {
				id: scrollbar
			}
		}

		Rectangle {
			implicitHeight: 1
			Layout.fillWidth: true
			color: Theme.console.spacer
		}

		Rectangle {
			height: 32
			color: Theme.console.input.background
			Layout.preferredHeight: height
			Layout.maximumHeight: height
			Layout.minimumHeight: height
			Layout.fillWidth: true

			TextInput {
				objectName: "ConsoleInput"
				height: 16
				anchors.fill: parent
				anchors.margins: 8

				focus: true
				color: Theme.console.input.text
				selectByMouse: true
				verticalAlignment: Text.AlignVCenter
				font.pixelSize: 13
				font.family: "Roboto Light"
				renderType: Text.NativeRendering

				signal commandEntered(string text)

				onAccepted: {
					console.log(text)
					commandEntered(text)
					text = ""
				}
			}
		}
	}
}

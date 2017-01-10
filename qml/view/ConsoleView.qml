import QtQuick 2.5
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import Picore 1.0
import Picore.Components 1.0

View {
	toolbar: Row {
		spacing: 5
		anchors.fill: parent
		z: 200

		Item{width: 5; height: 1}

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

			checked: pico.settings.value("Console/AutoScroll", "true") === "true";
			onCheckedChanged: pico.settings.setValue("Console/AutoScroll", checked);

			tooltip: PicoToolTip {
				text: "Enable autoscrolling"
			}
		}
	}

	Rectangle {
		color: theme.console.background
		anchors.fill: parent

		ListView {
			id: logview
			boundsBehavior: Flickable.StopAtBounds
			flickableDirection: Flickable.VerticalFlick
			anchors.fill: parent
			anchors.leftMargin: 5
			anchors.rightMargin: 5
			anchors.bottomMargin: 5
			anchors.topMargin: 5

			property var consolecolors: [
				theme.console.log.debug,
				theme.console.log.warning,
				theme.console.log.critical,
				theme.console.log.fatal,
				theme.console.log.info
			]

			model: pico.logModel

			delegate: Text {
				text: record
				color: logview.consolecolors[type]
				anchors.left: parent.left
				anchors.right: parent.right
				anchors.rightMargin: 10
				textFormat: Text.PlainText
				wrapMode: Text.WordWrap
				font.pointSize: 11
				font.family: "Courier"
			//	ListView.onAdd: if (autoscroll.checked) logview.positionViewAtEnd();
			}

			ScrollBar.vertical: ScrollBar {
				id: scrollbar
				width: 5
				contentItem: Rectangle {
					color: theme.console.scrollbar
					anchors.left: parent.left
					anchors.right: parent.right
					height: parent.height * parent.size
					y: parent.height * parent.position
				}
			}
		}
	}
}

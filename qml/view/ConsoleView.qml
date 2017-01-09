import QtQuick 2.5
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import Picore 1.0
import Picore.Components 1.0

View {
	toolbar: Row {
		spacing: 5
		anchors.fill: parent

		Item{width: 5; height: 1}

		PicoToolButton {
			id: clearButton
			text: "\uF12D"
			anchors.verticalCenter: parent.verticalCenter
			onClicked: pico.logModel.clear()
			pressedColor: theme.toolbar.button.pressed
			hoveredColor: theme.toolbar.button.hovered
		}

		PicoToolCheckBox {
			text: "\uF07d"
			anchors.verticalCenter: parent.verticalCenter

			hoveredColor: theme.toolbar.button.hovered
			enabledColor: theme.toolbar.button.checked
			disabledColor: theme.toolbar.button.unchecked

			checked: pico.settings.value("Console/AutoScroll", "true") === "true";
			onCheckedChanged: pico.settings.setValue("Console/AutoScroll", checked);
		}
	}

	Rectangle {
		color: theme.console.background
		anchors.fill: parent
		clip: true

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

/*	ColumnLayout {
		anchors.fill: parent
		anchors.margins: 10

		Rectangle {
			color: "#F7F7F7"
			Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
			Layout.fillHeight: true
			Layout.fillWidth: true
			clip: true

			ListView {
				id: logview
				boundsBehavior: Flickable.StopAtBounds
				flickableDirection: Flickable.VerticalFlick
				anchors.fill: parent
				anchors.leftMargin: 5
				anchors.rightMargin: 5
				anchors.bottomMargin: 5
				anchors.topMargin: 5

				model: pico.logModel

				delegate: Text {
					text: record
					color: ["#222222", "#FFAF00", "#FF2222", "#FF5555", "#000000"][type]
					anchors.left: parent.left
					anchors.right: parent.right
					anchors.rightMargin: 10
					textFormat: Text.PlainText
					wrapMode: Text.WordWrap
					font.pixelSize: 12
					font.family: "Courier"
					ListView.onAdd: if (autoscroll.checked) logview.positionViewAtEnd();
				}

				ScrollBar.vertical: ScrollBar {
					id: scrollbar
					width: 5
					contentItem: Rectangle {
						color: "#B8B8B8"
						anchors.left: parent.left
						anchors.right: parent.right
						height: parent.height * parent.size
						y: parent.height * parent.position
					}
				}
			}
		}

		Row {
			spacing: 5

			PicoButton {
				id: clearButton
				text: "\uF12D"
				font.family: "FontAwesome"

				onClicked: logModel.clear()

				contentItem: Row {
					spacing: 3

					Text {
						text: "\uF12D"
						font.pointSize: 10
						font.family: "FontAwesome"
						anchors.verticalCenter: parent.verticalCenter
					}

					Text {
						font.family: "Roboto Light"
						font.pointSize: 10
						text: "Clear"
						anchors.verticalCenter: parent.verticalCenter
					}
				}
			}

			PicoCheckBox {
				id: autoscroll
				text: "Auto scroll"
				checked: pico.settings.value("Console/AutoScroll", "true") === "true";
				onCheckedChanged: pico.settings.setValue("Console/AutoScroll", checked);
			}
		}
	} */
}

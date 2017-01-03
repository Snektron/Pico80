import QtQuick 2.5
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import Picore 1.0
import Picore.Components 1.0

View {
	ColumnLayout {
		id: columnlayout1
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

				model: logModel

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
			Button {
				implicitHeight: 20

				Row {
					anchors.centerIn: parent
					spacing: 3

					Text {
						text: "\uF12D"
						font.pointSize: 10
						font.family: "FontAwesome"
					}
					Text {
						text: "Clear"
						font.pointSize: 10
						font.family: "Roboto"
					}
				}

				onClicked: logModel.clear()
			}

			PicoCheckBox {
				id: autoscroll
				text: "Auto scroll"
				checked: settings.value("console/autoscroll", "true") === "true";
				onCheckedChanged: settings.setValue("console/autoscroll", checked);
			}
		}
	}
}

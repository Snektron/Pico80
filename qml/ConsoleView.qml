import QtQuick 2.5
import QtQuick.Controls.Material 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

RectangularGlow {
	glowRadius: 3
	spread: 0.2
	color: "#E0E0E0"
	cornerRadius: glowRadius

	Rectangle {
		color: "#ffffff"
		anchors.fill: parent
		clip: true

		ColumnLayout {
			id: columnlayout1
			anchors.fill: parent
			anchors.leftMargin: 10
			anchors.rightMargin: 10
			anchors.bottomMargin: 10
			anchors.topMargin: 10

			Rectangle {
				id: rectangle1
				color: "#E7E7E7"
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

					model: LogModel

					delegate: Text {
						text: record
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
						anchors.verticalCenter: parent.verticalCenter
						anchors.horizontalCenter: parent.horizontalCenter
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

					onClicked: LogModel.clear()
				}

				CheckBox {
					id: autoscroll
					font.family: "Roboto"
					text: "Auto scroll"
					implicitHeight: 20
					checked: true

					indicator: Rectangle {
						width: 18
						height: 18
						radius: 2
						color: "#FFFFFF"
						border.color: "#000000"
						anchors.verticalCenter: parent.verticalCenter

						Rectangle {
							width: 12
							height: 12
							radius: 3
							color: "#000000"
							anchors.horizontalCenter: parent.horizontalCenter
							anchors.verticalCenter: parent.verticalCenter
							visible: parent.parent.checked
						}
					}
				}
			}
		}
	}
}

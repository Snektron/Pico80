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

		Rectangle {
			color: "#F0F0F0"
			anchors.fill: parent
			anchors.leftMargin: 10;
			anchors.rightMargin: 10;
			anchors.bottomMargin: 10;
			anchors.topMargin: 10;
			clip: true

			ListView {
				id: logview
				boundsBehavior: Flickable.StopAtBounds
				flickableDirection: Flickable.VerticalFlick
				anchors.fill: parent

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
	}
}

import QtQuick 2.5
import QtQuick.Controls.Material 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

RectangularGlow {
	glowRadius: 3
	spread: 0.2
	color: "#D8D8D8"
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

			Flickable {
				id: flickable
				boundsBehavior: Flickable.StopAtBounds
				flickableDirection: Flickable.VerticalFlick
				anchors.fill: parent

				TextArea.flickable: TextArea {
					id: log
					objectName: "Log"
					text: ""
					textFormat: Text.PlainText
					wrapMode: Text.WordWrap
					font.pixelSize: 12
					font.family: "Courier"
				}

				ScrollBar.vertical: ScrollBar {
					id: scrollbar
					contentItem: Rectangle {
						color: "#B8B8B8"
						anchors.left: parent.left
						anchors.right: parent.right
						implicitWidth: 5
						height: parent.height * parent.size
						y: parent.height * parent.position
					}
				}
			}
		}
	}
}

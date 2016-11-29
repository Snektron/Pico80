import QtQuick 2.5
import QtQuick.Controls.Material 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

RectangularGlow {
	glowRadius: 3
	spread: 0.2
	color: "#E8E8E8"
	cornerRadius: glowRadius

	Rectangle {
		color: "#ffffff"
		anchors.fill: parent

		Text {
			id: log
			objectName: "Log"
			text: ""
			textFormat: Text.PlainText
			wrapMode: Text.WordWrap
			styleColor: "#000000"
			anchors.rightMargin: 10
			anchors.leftMargin: 10
			anchors.bottomMargin: 10
			anchors.topMargin: 10
			anchors.fill: parent
			font.pixelSize: 12
			font.family: "Courier"
		}
	}

}

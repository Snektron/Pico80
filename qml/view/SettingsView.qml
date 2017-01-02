import QtQuick 2.5
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Controls.Universal 2.0
import QtPositioning 5.7
import "../components"

View {
	Column {
		anchors.fill: parent
		anchors.margins: 10
		spacing: 10

		Text {
			text: "Settings"
			font.pointSize: 13
			font.family: "Roboto Light"
		}

		SettingsGroup { text: "General" }

		Row {
			spacing: 10

			Text {
				text: "Emulator plugin"
				font.pointSize: 10
				font.family: "Roboto"
			}
		}
	}
}

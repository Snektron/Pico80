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

			ComboBox {
				model: ["Test", "Test 1", "Test 2"]
				implicitHeight: 15
				font.family: "Roboto Light"

				indicator: Text {
					anchors.right: parent.right
					anchors.rightMargin: 3
					anchors.verticalCenter: parent.verticalCenter
					color: "#101010"
					text: "\uF107"
					font.pointSize: 10
					font.family: "FontAwesome"
				}
			}
		}
	}
}

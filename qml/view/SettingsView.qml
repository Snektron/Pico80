import QtQuick 2.5
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Controls.Universal 2.0
import QtPositioning 5.7
import Picore 1.0
import Picore.Settings 1.0
import Picore.Components 1.0

View {
	SettingGroup {
		text: "Settings"
		anchors.fill: parent
		anchors.margins: 10
		font.pointSize: 13

		SettingGroup {
			text: "General"

			SettingItem {
				text: "Test"

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

			SettingItem {
				text: "Test 2"

				PicoCheckBox {

				}
			}
		}
	}
}

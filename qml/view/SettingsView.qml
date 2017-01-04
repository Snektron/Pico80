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
				text: "Emulator plugin"

				PicoComboBox {
					textRole: "name"
					model: pico.pluginModel
					id: pluginSetting

					delegate: ItemDelegate {
						width: pluginSetting.width
						implicitHeight: 15
						highlighted: pluginSetting.highlightedIndex == index

						contentItem: Text {
							text: name
							font.family: "Roboto Light"
							verticalAlignment: Text.AlignVCenter
							anchors.verticalCenter: parent.verticalCenter
							anchors.left: parent.left
							anchors.leftMargin: 3
						}
					}
				}
			}

			SettingItem {
				text: "Test 2"

				PicoCheckBox {
				}
			}

			SettingItem {
				text: "Test 3"

				PicoButton {
					text: "Test"
				}
			}
		}
	}
}

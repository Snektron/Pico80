import QtQuick 2.5
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Controls.Universal 2.0
import QtPositioning 5.7
import Picore 1.0
import Picore.Settings 1.0
import Picore.Components 1.0

View {
	Item {
		anchors.fill: parent
		anchors.margins: 10

		SettingGroup {
			text: "Settings"
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
						currentIndex: 0

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

						onActivated: updatePlugin(currentIndex)
						Component.onCompleted: {
							var text = pico.settings.value("General/Emulator", "none");
							var index = find(text);
							if (index === -1)
								index = 0;
							currentIndex = index;
							updatePlugin(currentIndex)
						}

						function updatePlugin(index)
						{
							pico.settings.setValue("General/Emulator", currentText);
							pico.setPlugin(pico.pluginModel.fileForPlugin(index));
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
						tooltip: PicoToolTip {
							text: "dit is een heel lang stukje text om dit dingetje te testen.nl"
						}
					}
				}

				SettingItem {
					text: "Test 4"

					PicoCheckBox {
					}
				}
			}
		}
	}
}

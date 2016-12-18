import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import Pico80 1.0

Rectangle {
    id: base
	color: "#F1F1F1"

    FontLoader { source: "/fonts/Roboto-Regular.ttf" }
    FontLoader { source: "/fonts/fontawesome-webfont.ttf"}

	Rectangle {
		id: toolbar
		color: "#2D313F"
		anchors.left: parent.left
		anchors.top: parent.top
		anchors.bottom: parent.bottom
		width: 80

		ColumnLayout {
			spacing: 0
			anchors.fill: parent

			SidebarButton {
				id: button1
				caption: "Dashboard"
				icon: "\uF0e4"
				checked: true
				Layout.alignment: Qt.AlignLeft | Qt.AlignTop
				Layout.minimumHeight: 64
				Layout.maximumHeight: 64
				Layout.preferredHeight: 64
				Layout.fillWidth: true
				Layout.fillHeight: true

				onActivated: {
					button2.checked = false
					button3.checked = false
					button4.checked = false
					menuview.state = ""
					menuview.currentIndex = 0
				}

				onDeactivated: {
					menuview.state = 'hidden'
					menuview.currentIndex = -1
				}
			}

			SidebarButton {
				id: button2
				caption: "Debug"
				icon: "\uF188"
				anchors.top: button1.bottom
				Layout.alignment: Qt.AlignLeft | Qt.AlignTop
				Layout.minimumHeight: 64
				Layout.maximumHeight: 64
				Layout.preferredHeight: 64
				Layout.fillWidth: true
				Layout.fillHeight: true

				onActivated: {
					button1.checked = false
					button3.checked = false
					button4.checked = false
					menuview.state = ""
					menuview.currentIndex = 1
				}

				onDeactivated: {
					menuview.state = 'hidden'
					menuview.currentIndex = -1
				}
			}

			SidebarButton {
				id: button3
				caption: "Console"
				icon: "\uF120"
				anchors.top: button2.bottom
				Layout.alignment: Qt.AlignLeft | Qt.AlignTop
				Layout.minimumHeight: 64
				Layout.maximumHeight: 64
				Layout.preferredHeight: 64
				Layout.fillWidth: true
				Layout.fillHeight: true

				onActivated: {
					button1.checked = false
					button2.checked = false
					button4.checked = false
					menuview.state = ""
					menuview.currentIndex = 2
				}

				onDeactivated: {
					menuview.state = 'hidden'
					menuview.currentIndex = -1
				}
			}

			SidebarButton {
				id: button4
				caption: "Settings"
				icon: "\uF085"
				anchors.top: button3.bottom
				Layout.alignment: Qt.AlignLeft | Qt.AlignTop
				Layout.minimumHeight: 64
				Layout.maximumHeight: 64
				Layout.preferredHeight: 64
				Layout.fillWidth: true
				Layout.fillHeight: true

				onActivated: {
					button1.checked = false
					button2.checked = false
					button3.checked = false
					menuview.state = ""
					menuview.currentIndex = 3
				}

				onDeactivated: {
					menuview.state = 'hidden'
					menuview.currentIndex = -1
				}
			}
		}
	}

	Rectangle {
		id: mainview
		color: "#00000000"
		anchors.left: toolbar.right
		anchors.top: parent.top
		anchors.right: parent.right
		anchors.bottom: parent.bottom

		SplitView {
			anchors.fill: parent
			anchors.rightMargin: 10
			anchors.leftMargin: 10
			anchors.bottomMargin: 10
			anchors.topMargin: 10

			onWidthChanged: {
				if (width > 0 && menuview_container.width > width - 250 - 10)
					menuview_container.width = width - 250 - 10;
			}

			handleDelegate: Rectangle {
				width: 10
				color: "#00000000"
			}

			Rectangle {
				id: menuview_container
				color: "#00000000"
				Layout.fillHeight: true
				Layout.minimumWidth: 300
				width: 500;

				StackLayout {
					id: menuview
					anchors.fill: parent
					currentIndex: 0

					states: [
						State {
							name: "hidden"
							PropertyChanges {
								target: menuview_container;
								Layout.preferredWidth: 0
								visible: false
								Layout.fillWidth: false
							}
						}
					]

					DashboardView {}
					DebugView {}
					ConsoleView {}
					SettingsView {}
				}
			}

			RectangularGlow {
				id: display_container
				Layout.minimumWidth: 250
				Layout.fillWidth: true

				onWidthChanged: display.updateDimensions();
				onHeightChanged: display.updateDimensions();

				glowRadius: 3
				spread: 0.2
				color: "#E0E0E0"
				cornerRadius: glowRadius

				Rectangle {
					color: "#FFFFFF"
					anchors.fill: parent

					Display {
						id: display
						objectName: "Display"
						anchors.horizontalCenter: parent.horizontalCenter
						anchors.verticalCenter: parent.verticalCenter

						function updateDimensions()
						{
							width = height = Math.min(parent.width, parent.height);
						}
					}
				}
			}
		}
	}
}

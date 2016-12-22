import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import Pico80 1.0
import "view"

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

		SideBar {
			id: sidebar

			onCurrentChanged: {
				if (current) {
					menuview.state = ""
					menuview.currentIndex = current.index
				} else
					menuview.state = "hidden"
			}
		}

		Column {
			anchors.fill: parent

			SideBarButton {
				id: sb_dashboard
				sidebar: sidebar
				caption: "Dashboard"
				icon: "\uF0e4"
				checked: true
				index: 0
			}

			SideBarButton {
				id: sb_debug
				sidebar: sidebar
				caption: "Debug"
				icon: "\uF188"
				index: 1
			}

			SideBarButton {
				id: sb_console
				sidebar: sidebar
				caption: "Console"
				icon: "\uF120"
				index: 2
			}

			SideBarButton {
				id: sb_settings
				sidebar: sidebar
				caption: "Settings"
				icon: "\uF085"
				index: 3
			}
		}
	}

	Rectangle {
		color: "#00000000"
		anchors.left: toolbar.right
		anchors.top: parent.top
		anchors.right: parent.right
		anchors.bottom: parent.bottom

		SplitView {
			anchors.fill: parent

			onWidthChanged: {
				if (width > 0 && mainview_container.width > width - 250 - 10)
					mainview_container.width = width - 250 - 10;
			}

			handleDelegate: Rectangle {
				width: 1
				color: "#BBBBBB"
			}

			Rectangle {
				id: mainview_container
				color: "#00000000"
				Layout.minimumWidth: 300
				width: 400;

				StackLayout {
					id: menuview
					anchors.fill: parent
					currentIndex: 0

					states: [
						State {
							name: "hidden"
							PropertyChanges {
								target: mainview_container;
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

			Rectangle {
				color: "#FFFFFF"
				id: display_container
				Layout.minimumWidth: 250
				Layout.minimumHeight: 250

				onWidthChanged: display.updateDimensions();
				onHeightChanged: display.updateDimensions();

				Display {
					id: display
					objectName: "Display"
					anchors.centerIn: parent

					function updateDimensions()
					{
						var size = Math.min(parent.width, parent.height) - 10;
						width = height = size;
					}
				}
			}
		}
	}
}

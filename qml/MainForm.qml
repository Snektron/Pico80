import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import Picore.Components 1.0
import "components"
import "view"

Rectangle {
    id: base
	color: "#F1F1F1"

	FontLoader { source: "/fonts/Roboto-Regular.ttf" }
	FontLoader { source: "/fonts/Roboto-Light.ttf" }
	FontLoader { source: "/fonts/Roboto-Thin.ttf" }
	FontLoader { source: "/fonts/OpenSans-Regular.ttf" }
	FontLoader { source: "/fonts/OpenSans-Light.ttf" }
	FontLoader { source: "/fonts/fontawesome-webfont.ttf"}

	Rectangle {
		id: sidebar_base
		color: theme.sidebar.primary
		anchors.left: parent.left
		anchors.top: parent.top
		anchors.bottom: parent.bottom
		width: 80

		PicoToolBar {
			id: bartoolbar
			color: theme.sidebar.toolbar.primary
			shadowColor: theme.sidebar.toolbar.shadow
		}

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
			objectName: "SideBar"
			anchors.top: bartoolbar.bottom
			anchors.bottom: parent.bottom
			anchors.left: parent.left
			anchors.right: parent.right

			SideBarButton {
				id: sb_debug
				objectName: "Test"
				sidebar: sidebar
				index: 0
				caption: "Debug"
				icon: "\uF188"
				checked: true
			}

			SideBarButton {
				id: sb_console
				sidebar: sidebar
				index: 1
				caption: "Console"
				icon: "\uF120"
			}

			SideBarButton {
				id: sb_settings
				index: 2
				sidebar: sidebar
				caption: "Settings"
				icon: "\uF085"
			}
		}
	}

	SplitView {
		anchors.left: sidebar_base.right
		anchors.top: parent.top
		anchors.right: parent.right
		anchors.bottom: parent.bottom

		onWidthChanged: {
			if (width > 0 && mainview_container.width > width - 300 - 1)
				mainview_container.width = width - 300 - 1;
		}

		handleDelegate: Rectangle {
			width: 1
			color: theme.spacer

			PicoToolBar {
				color: theme.toolbar.primary
				shadowColor: theme.toolbar.shadow

				Rectangle {
					width: 1
					anchors.top: parent.top
					anchors.bottom: parent.bottom
					anchors.topMargin: 5
					anchors.bottomMargin: 5
					color: theme.toolbar.spacer
				}
			}
		}

		Rectangle {
			id: mainview_container
			Layout.minimumWidth: 300
			width: 400

			PicoToolBar {
				id: toolbar
				color: theme.toolbar.primary
				shadowColor: theme.toolbar.shadow
			}

			StackLayout {
				id: menuview
				objectName: "View"
				anchors.top: toolbar.bottom
				anchors.left: parent.left
				anchors.right: parent.right
				anchors.bottom: parent.bottom
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

				Component.onCompleted: updateToolbar(currentIndex)
				onCurrentIndexChanged: updateToolbar(currentIndex)
				onStateChanged: updateToolbar(state === "" ? currentIndex : -1)

				function updateToolbar(index) {
					toolbar.items = index === -1 ? null : children[index].toolbar;
				}

				DebugView {}
				ConsoleView {}
				SettingsView {}
			}
		}

		Rectangle {
			Layout.minimumWidth: 300
			Layout.minimumHeight: 250

			PicoToolBar {
				id: emulatortoolbar
				color: theme.toolbar.primary
				shadowColor: theme.toolbar.shadow
			}

			Item {
				id: display_container
				objectName: "DisplayContainer"

				anchors.top: emulatortoolbar.bottom
				anchors.left: parent.left
				anchors.right: parent.right
				anchors.bottom: parent.bottom

				function updateDisplay() {
					for (var i = 0; i < children.length; i++)
						if (children[i].objectName === "Display")
							children[i].anchors.fill = display_container
				}
			}
		}
	}
}

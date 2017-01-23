import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import Pico80.Components 1.0
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

	Item {
		id: settings
		property bool autoscroll: Settings.value("Console/AutoScroll", "true") === "true";

		Component.onDestruction: {
			Settings.setValue("Console/AutoScroll", autoscroll);
		}
	}

	Rectangle {
		id: sidebar_base
		color: Theme.sidebar.primary
		anchors.left: parent.left
		anchors.top: parent.top
		anchors.bottom: parent.bottom
		width: 80

		PicoToolBar {
			id: bartoolbar
			color: Theme.sidebar.toolbar.primary
			shadowColor: Theme.sidebar.toolbar.shadow
		}

		SideBar {
			id: sidebar
			objectName: "SideBar"
			container: menucontainer

			anchors.top: bartoolbar.bottom
			anchors.left: parent.left
			anchors.right: parent.right
			anchors.bottom: parent.bottom
		}
	}

	SplitView {
		anchors.left: sidebar_base.right
		anchors.top: parent.top
		anchors.right: parent.right
		anchors.bottom: parent.bottom

		onWidthChanged: {
			if (width > 0 && menucontainer.width > width - 300 - 1)
				menucontainer.width = width - 300 - 1;
		}

		handleDelegate: Rectangle {
			width: 1
			color: Theme.spacer

			PicoToolBar {
				Rectangle {
					width: 1
					anchors.top: parent.top
					anchors.bottom: parent.bottom
					anchors.topMargin: 5
					anchors.bottomMargin: 5
					color: Theme.toolbar.spacer
				}
			}
		}

		ViewContainer {
			id: menucontainer
			objectName: "SideBarContainer"
			Layout.minimumWidth: 300
			width: 400

			DebugView {
				id: debugview
			}

			ConsoleView {
				id: consoleview
			}

			SettingsView {
				id: settingsview
			}
		}

		Rectangle {
			Layout.minimumWidth: 300
			Layout.minimumHeight: 250

			Item {
				id: display_container
				objectName: "DisplayContainer"
				anchors.fill: parent

				function updateDisplay() {
					for (var i = 0; i < children.length; i++)
						if (children[i].objectName === "Display")
							children[i].anchors.fill = display_container
				}
			}
		}
	}
}

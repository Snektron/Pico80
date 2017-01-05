import QtQuick 2.5
import QtQuick.Controls 2.0
import QtPositioning 5.7

Button {
	property string caption: "Button"
	property string icon: "\uF188"
	property int index: 0
	property var sidebar: null

	width: 80
	height: 64

	id: button
	checkable: true
	hoverEnabled: true

	background: Rectangle {
		color: {
			if (button.checked)
				return theme.sidebar.checked;
			else if( button.hovered || button.down)
				return theme.sidebar.down
			else
				return theme.sidebar.primary
		}

		Rectangle {
			anchors.left: parent.left
			anchors.top: parent.top
			anchors.bottom: parent.bottom
			width: 5
			color: theme.sidebar.accent
			visible: button.checked
		}
	}

	Text {
		color: "#EEEEEE"
		text: button.icon
		font.pointSize: 15
		font.family: "FontAwesome"
		anchors.bottom: button.verticalCenter
		anchors.horizontalCenter: button.horizontalCenter
	}

	Text {
		color: "#EEEEEE"
		text: button.caption
		anchors.topMargin: 5
		font.pointSize: 10
		font.family: "Roboto"
		anchors.top: button.verticalCenter
		anchors.horizontalCenter: button.horizontalCenter
	}

	Component.onCompleted: {
		if (checked && sidebar)
			sidebar.setCurrent(this);
	}

	onClicked: {
		if (sidebar) {
			if (checked)
				sidebar.setCurrent(this);
			else
				sidebar.setCurrent(null);
		}
	}
}

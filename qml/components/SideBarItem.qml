import QtQuick 2.5
import QtQuick.Controls 2.0
import QtPositioning 5.7

Button {
	property string caption: "Button"
	property string icon: "\uF188"
	property int index: 0
	property var sidebar: null

	property Component content: null
	property Component toolbar: null

	width: 80
	height: 64

	id: button
	checkable: true
	hoverEnabled: true

	background: Rectangle {
		color: {
			if (button.checked)
				return Theme.sidebar.button.selected;
			else if(button.hovered || button.down)
				return Theme.sidebar.button.hovered;
			else
				return Theme.sidebar.button.primary;
		}

		Rectangle {
			anchors.left: parent.left
			anchors.top: parent.top
			anchors.bottom: parent.bottom
			width: 5
			color: Theme.sidebar.button.accent
			visible: button.checked
		}
	}

	Text {
		color: button.checked ? Theme.sidebar.icon.selected : Theme.sidebar.icon.primary
		text: button.icon
		font.pointSize: 15
		font.family: "FontAwesome"
		anchors.bottom: button.verticalCenter
		anchors.horizontalCenter: button.horizontalCenter
	}

	Text {
		color: button.checked ? Theme.sidebar.text.selected : Theme.sidebar.text.primary
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

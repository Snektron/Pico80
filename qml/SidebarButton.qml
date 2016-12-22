import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Button {
	property alias caption: caption.text
	property alias icon: icon.text
	property var sidebar: null // using SidebarButton instead of var crashes
	property int index: 0

    id: button
    checkable: true
	hoverEnabled: true

	width: 80
	height: 64

    background: Rectangle {
		color: button.checked ? "#20232F" : button.hovered || button.down ? "#3A4051" : "#2D313F"

		Rectangle {
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: 5
			color: "#6BB0DA"
			visible: button.checked
		}
    }

    Text {
		id: icon
		color: "#EEEEEE"
        font.pointSize: 15
        font.family: "FontAwesome"
        anchors.bottom: button.verticalCenter
        anchors.horizontalCenter: button.horizontalCenter
    }

    Text {
		id: caption
		color: "#EEEEEE"
        anchors.topMargin: 5
        font.pointSize: 10
        font.family: "Roboto"
        anchors.top: button.verticalCenter
        anchors.horizontalCenter: button.horizontalCenter
    }

	function check() {
		checked = true
		clicked()
	}

    onClicked: {
		if (sidebar)
		{
			if (checked)
				sidebar.setCurrent(this)
			else
				sidebar.setCurrent(null)
		}
    }

	Component.onCompleted: {
		if (checked && sidebar)
			sidebar.setCurrent(this)
	}
}

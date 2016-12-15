import QtQuick 2.5
import QtQuick.Controls.Material 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3
import QtPositioning 5.7

Button {
    property string caption: "Button"
    property string icon: "\uF188"

    signal activated
    signal deactivated

    id: button
    checkable: true

    background: Rectangle {
        color: button.down || button.checked ? "#20232F" : "#2D313F"

        Rectangle {
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: 5
			color: button.checked ? "#6BB0DA" : "#20232F"
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

    onClicked: {
        if (checked)
            button.activated()
        else
            button.deactivated()
    }
}

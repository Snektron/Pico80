import QtQuick 2.5
import QtQuick.Controls.Material 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3
import QtPositioning 5.7
import Pico80 1.0

Rectangle {
    id: base
    width: 640
    height: 480
    color: "#DEDEDE"

    FontLoader { source: "/fonts/Roboto-Regular.ttf" }
    FontLoader { source: "/fonts/fontawesome-webfont.ttf"}

    RowLayout {
        id: rowLayout2
        spacing: 0
        anchors.fill: parent

        Rectangle {
            id: toolbar
            width: 200
            height: 200
            color: "#2D313F"
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            Layout.minimumWidth: 80
            Layout.maximumWidth: 80
            Layout.preferredWidth: 80
            Layout.fillHeight: true
            Layout.fillWidth: true

            ColumnLayout {
                id: columnLayout2
                spacing: 0
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.left: parent.left
                anchors.top: parent.top

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
                    caption: "Settings"
                    icon: "\uF085"
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
                        menuview.state = ""
                        menuview.currentIndex = 2
                    }

                    onDeactivated: {
                        menuview.state = 'hidden'
                        menuview.currentIndex = -1
                    }
                }
            }
        }

        Rectangle {
            id: rectangle4
            width: 200
            height: 200
            color: "#00000000"
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.fillHeight: true
            Layout.fillWidth: true

            RowLayout {
                id: rowLayout1
                anchors.rightMargin: 10
                anchors.leftMargin: 10
                anchors.bottomMargin: 10
                anchors.topMargin: 10
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.fillHeight: true
                Layout.fillWidth: true
                spacing: 10
                anchors.fill: parent

                Rectangle {
                    id: rectangle6
                    width: 200
                    height: 200
                    color: "#00000000"
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    StackLayout {
                        id: menuview
                        width: 200
                        height: 200
                        anchors.fill: parent
                        currentIndex: 0

                        states: [
                            State {
                                name: "hidden"
                                PropertyChanges {
                                    target: rectangle6;
                                    Layout.preferredWidth: 0
                                    visible: false
                                }
                            }
                        ]

                        Rectangle {
                            id: rectangle1
                            width: 200
                            height: 200
                            color: "#ff0000"
                            radius: 8
                            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                        }

                        Rectangle {
                            id: rectangle2
                            width: 200
                            height: 200
                            color: "#ff00ff"
                            radius: 8
                            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                        }

                        Rectangle {
                            id: rectangle3
                            width: 200
                            height: 200
                            color: "#ffff00"
                            radius: 8
                            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                        }
                    }
                }

                Rectangle {
					id: display_container
					width: 200
					height: 200
                    color: "#00000000"
                    opacity: 1
                    visible: true
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    anchors.topMargin: 10
                    anchors.bottomMargin: 10
                    anchors.leftMargin: 10
                    anchors.rightMargin: 10

					Display {
						id: display
						objectName: "Display"
						anchors.fill: parent
					}
                }
            }
        }
    }
}

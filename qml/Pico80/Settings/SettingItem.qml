import QtQuick 2.0

Row {
	id: content
	property alias text: title.text
	property alias font: title.font
	default property alias _contentChildren: content.data
	spacing: 10

	Text {
		id: title
		font.pointSize: 10
		font.family: "Roboto Light"
		renderType: Text.NativeRendering
	}
}

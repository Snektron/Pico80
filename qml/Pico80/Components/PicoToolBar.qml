import QtQuick 2.5
import QtQuick.Controls 2.0
import QtGraphicalEffects 1.0

Rectangle {
	id: toolbar
	implicitHeight: 32
	anchors.left: parent.left
	anchors.right: parent.right
	color: Theme.toolbar.primary
	z: 100

	property alias shadowColor: gradientBegin.color
	property alias shadowHeight: shadow.height
	property alias items: items.sourceComponent

	Loader {
		id: items
		anchors.fill: parent
	}

	LinearGradient {
		id: shadow
		anchors.top: toolbar.bottom
		anchors.left: toolbar.left
		anchors.right: toolbar.right
		height: 3

		gradient: Gradient {
			GradientStop {
				id: gradientBegin
				position: 0.0
				color: Theme.toolbar.shadow
			}

			GradientStop {
				position: 1.0
				color: "#00000000"
			}
		}
	}
}

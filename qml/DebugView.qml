import QtQuick 2.5
import QtQuick.Controls.Material 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

RectangularGlow {
	glowRadius: 3
	spread: 0.2
	color: "#D8D8D8"
	cornerRadius: glowRadius

	Rectangle {
		color: "#ffffff"
		anchors.fill: parent
	}
}

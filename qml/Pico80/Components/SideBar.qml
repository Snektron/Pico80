import QtQuick 2.5

Column {
	id: root

	property ViewContainer container: null
	property int currentIndex: 0

	onCurrentIndexChanged: updateContainer()
	Component.onCompleted: updateContainer()

	function updateContainer() {
		if (container) {
			if (currentIndex >= 0)
				container.show(currentIndex)
			else
				container.hide()
		}
	}

	Repeater {
		id: repeater
		model: container.children

		SideBarButton {
			caption: modelData.caption
			icon: modelData.icon
			checked: currentIndex == index
			onClicked: currentIndex = currentIndex == index ? -1 : index
			Component.onDestruction: {
				if (container && container.children.length >= 0)
					currentIndex = 0
				else
					currentIndex = -1
			}

			Connections {
				target: modelData
				onShow: currentIndex = index
			}
		}
	}
}

import QtQuick 2.5

Item {
	property SideBarButton current: null

	function setCurrent(button) {
		if (current)
			current.checked = false
		current = button
		if (current)
			current.checked = true
	}
}

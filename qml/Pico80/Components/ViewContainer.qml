import QtQuick 2.0
import QtQuick.Layouts 1.3

StackLayout {
	id: root
	currentIndex: 0
	states: [
		State {
			name: "hidden"
			PropertyChanges {
				target: root
				visible: false
			}
		}
	]

	function hide() {
		state = "hidden"
	}

	function show(index) {
		state = ""
		currentIndex = index
	}
}

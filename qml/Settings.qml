import QtQuick 2.0

Item {
	property bool autoscroll: pico.settings.value("Console/AutoScroll", "true") === "true";

	Component.onDestruction: {
		pico.settings.setValue("Console/AutoScroll", autoscroll);
	}
}

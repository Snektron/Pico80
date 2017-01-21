#include "core/PicoQmlEngine.h"
#include <QQmlComponent>
#include <QQmlContext>
#include <QDebug>

PicoQmlEngine::PicoQmlEngine()
{
	addImportPath("qrc:/qml/");
}

QQuickItem* PicoQmlEngine::setDisplay(QUrl file)
{
	QQmlComponent component(this, file);
	QQuickItem *display = qobject_cast<QQuickItem*>(component.create());
	if (display)
		setDisplay(display);
	else
	{
		qCritical() << "Failed to load" << file.fileName();
		qCritical() << component.errors();
	}
	return display;
}

void PicoQmlEngine::setDisplay(QQuickItem *display)
{
	QQuickItem *displayContainer = findChild<QQuickItem*>("DisplayContainer");
	display->setObjectName("Display");
	display->setParentItem(displayContainer);
	QMetaObject::invokeMethod(displayContainer, "updateDisplay");
}

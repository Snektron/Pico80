#include "core/PicoQmlEngine.h"
#include <QQmlComponent>
#include <QQmlContext>
#include <QDebug>

PicoQmlEngine::PicoQmlEngine()
{
	addImportPath("qrc:/qml/");
}

QQuickItem* PicoQmlEngine::loadComponent(QUrl file)
{
	QQmlComponent component(this, file);
	QQuickItem * item = qobject_cast<QQuickItem*>(component.create());
	if (!item)
	{
		qCritical() << "Failed to load" << file.fileName();
		qCritical() << component.errors();
	}
	return item;
}

void PicoQmlEngine::setDisplay(QQuickItem *display)
{
	QQuickItem *displayContainer = findChild<QQuickItem*>("DisplayContainer");
	display->setObjectName("Display");
	display->setParentItem(displayContainer);
	QMetaObject::invokeMethod(displayContainer, "updateDisplay");
}

void PicoQmlEngine::addSidebarView(QQuickItem *item, QString id)
{
	QQuickItem *sideBarContainer = findChild<QQuickItem*>("SideBarContainer");
	item->setParentItem(sideBarContainer);
	item->setProperty("id", id);
}

#include "DefaultEmulatorContext.h"
#include <QDebug>

DefaultEmulatorContext::DefaultEmulatorContext(IPicoEngine *engine)
{
	display = engine->qmlEngine()->loadComponent(QUrl("qrc:/qml/impl/Display.qml"));
	engine->qmlEngine()->setDisplay(display);
}

DefaultEmulatorContext::~DefaultEmulatorContext()
{
	delete display;
}

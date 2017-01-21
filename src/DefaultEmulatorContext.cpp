#include "DefaultEmulatorContext.h"
#include <QDebug>

DefaultEmulatorContext::DefaultEmulatorContext(IPicoEngine *engine)
{
	display = engine->qmlEngine()->setDisplay(QUrl("qrc:/qml/impl/Display.qml"));
}

DefaultEmulatorContext::~DefaultEmulatorContext()
{
	delete display;
}

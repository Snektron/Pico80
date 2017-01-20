#include "DefaultEmulatorContext.h"

DefaultEmulatorContext::DefaultEmulatorContext(IPicoQmlEngine *engine)
{
	display = engine->setDisplay(QUrl("qrc:/qml/impl/Display.qml"));
}

DefaultEmulatorContext::~DefaultEmulatorContext()
{
	delete display;
}

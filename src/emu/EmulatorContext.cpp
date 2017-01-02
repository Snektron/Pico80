#include "emu/EmulatorContext.h"
#include "gui/display/Display.h"

EmulatorContext::EmulatorContext(QmlPicoEngine *qmlEngine, IPlugin *plugin):
	display(Q_NULLPTR)
{
	loadDefaults();
	if (plugin)
		plugin->registerPlugin(pluginEngine);

	emulator = new EmulatorThread(&pluginEngine);
	createQmlComponents(qmlEngine);
}

EmulatorContext::~EmulatorContext()
{
	delete display;
	emulator->quit();
	delete emulator;
}

void EmulatorContext::start()
{
	emulator->start();
}

void EmulatorContext::loadDefaults()
{
	pluginEngine.registerDisplayQml(QUrl("qrc:/qml/impl/Display.qml"));
}

void EmulatorContext::createQmlComponents(QmlPicoEngine *qmlEngine)
{
	QQuickItem *displayContainer = qmlEngine->findChild<QQuickItem*>("DisplayContainer");
	display = pluginEngine.createDisplay(qmlEngine);
	display->setObjectName("Display");
	display->setParentItem(displayContainer);
	QMetaObject::invokeMethod(displayContainer, "updateDisplay");
}

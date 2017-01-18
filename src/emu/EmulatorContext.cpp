#include "emu/EmulatorContext.h"

EmulatorContext::EmulatorContext(QmlPicoEngine *qmlEngine, IPlugin *plugin):
	display(Q_NULLPTR)
{
	loadDefaults();
	if (plugin)
		plugin->registerPlugin(pluginEngine);

	createQmlComponents(qmlEngine);
	emulatorThread = new EmulatorThread(&pluginEngine);
	connect(emulatorThread, SIGNAL(started()),
			this, SLOT(onEmulatorThreadStarted()),
			Qt::QueuedConnection);
}

EmulatorContext::~EmulatorContext()
{
	emulatorThread->quit();
	delete emulatorThread;
	delete display;
}

void EmulatorContext::start()
{
	emulatorThread->start();
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

void EmulatorContext::onEmulatorThreadStarted()
{
	emit emulatorThread->initialize(display);
}

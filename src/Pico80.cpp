#include "Pico80.h"
#include <QQmlContext>
#include <picore/PluginEngine.h>
#include "gui/Logging.h"

Pico80::Pico80():
	emulator(Q_NULLPTR)
{
	Logging::installMessageHandler();
	qInfo() << "Starting";

	qmlEngine = new QmlPicoEngine();
	manager = new PluginManager();
	system = new System(manager);

	QQmlContext *ctx = qmlEngine->rootContext();
	ctx->setContextProperty("pico", system);

	qmlEngine->addImportPath("qrc:/qml/import/");
	qmlEngine->load(QUrl("qrc:/qml/main.qml"));
}

Pico80::~Pico80()
{
	Logging::removeMessageHandler();
	delete qmlEngine;
	delete emulator;
	delete system;
	delete manager;
}

void Pico80::setEmulatorPlugin(QString file)
{
	delete emulator;
	if (file != "")
	{
		IPlugin *plugin = manager->loadPluginByFile(file);
		if (plugin)
			qDebug() << "Activating plugin" << plugin->name();
		else
			qWarning() << "Failed to activate plugin" << file;

		emulator = new EmulatorContext(qmlEngine, plugin);
	}
	else
	{
		qDebug() << "Activating builtin plugin";
		emulator = new EmulatorContext(qmlEngine, Q_NULLPTR);
	}
	emulator->start();
}

void Pico80::start()
{
	QList<PluginDescriptor> plugins = manager->availablePlugins();
	if (plugins.size() > 0)
		setEmulatorPlugin(plugins[0].getFileName());
	else
		setEmulatorPlugin("");
}

void Pico80::quit()
{
	qInfo() << "Stopping";
}

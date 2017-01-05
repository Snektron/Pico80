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
	themeEngine = new ThemeEngine();

	QQmlContext *ctx = qmlEngine->rootContext();
	ctx->setContextProperty("pico", system);
	ctx->setContextProperty("theme", themeEngine->loadTheme());

	connect(system, SIGNAL(pluginChanged(QString)), this, SLOT(setEmulatorPlugin(QString)), Qt::QueuedConnection);

	qmlEngine->addImportPath("qrc:/qml/import/");
	qmlEngine->load(QUrl("qrc:/qml/main.qml"));

	emulator = new EmulatorContext(qmlEngine, Q_NULLPTR);
}

Pico80::~Pico80()
{
	Logging::removeMessageHandler();
	delete qmlEngine;
	delete emulator;
	delete system;
	delete themeEngine;
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

void Pico80::quit()
{
	qInfo() << "Stopping";
}

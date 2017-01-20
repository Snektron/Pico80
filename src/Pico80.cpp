#include "Pico80.h"
#include <QQmlContext>
#include <QDebug>
#include "gui/Logging.h"
#include "DefaultEmulatorContext.h"

Pico80::Pico80():
	emulator(Q_NULLPTR)
{
	Logging::installMessageHandler();
	qInfo() << "Starting";

	qmlEngine = new PicoQmlEngine();
	manager = new PluginManager();
	system = new System(manager);
	themeEngine = new ThemeEngine();

	QQmlContext *ctx = qmlEngine->rootContext();
	ctx->setContextProperty("pico", system);
	ctx->setContextProperty("theme", themeEngine->loadTheme());

	connect(system, SIGNAL(pluginChanged(QString)), this, SLOT(setEmulatorPlugin(QString)), Qt::QueuedConnection);

	qmlEngine->addImportPath("qrc:/qml/");
	qmlEngine->load(QUrl("qrc:/qml/main.qml"));

	emulator = new DefaultEmulatorContext(qmlEngine);
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
	emulator = Q_NULLPTR;
	if (file != "")
	{
		IPlugin *plugin = manager->loadPluginByFile(file);
		if (plugin)
		{
			qDebug() << "Activating plugin" << plugin->name();
			emulator = plugin->createContext(qmlEngine);
		}
		else
			qWarning() << "Failed to activate plugin" << file;
	}

	if (!emulator)
	{
		qDebug() << "Activating builtin plugin";
		emulator = new DefaultEmulatorContext(qmlEngine);
	}
}

void Pico80::quit()
{
	qInfo() << "Stopping";
}

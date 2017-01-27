#include "Pico80.h"
#include <QDebug>
#include <QString>
#include "gui/Logging.h"
#include "DefaultEmulatorContext.h"

Pico80::Pico80():
	emulator(Q_NULLPTR)
{
	Logging::installMessageHandler();
	qInfo() << "Starting";

	engine = new PicoEngine(QUrl("qrc:/qml/main.qml"));

	connect(engine, SIGNAL(pluginChanged(QString)), this, SLOT(setEmulatorPlugin(QString)));

	emulator = new DefaultEmulatorContext(engine);
}

Pico80::~Pico80()
{
	delete emulator;
	delete engine;
	Logging::removeMessageHandler();
}

void Pico80::setEmulatorPlugin(QString file)
{
	delete emulator;
	emulator = Q_NULLPTR;
	if (file != "")
	{
		IPlugin *plugin = engine->pluginManager()->loadPluginByFile(file);
		if (plugin)
		{
			qDebug() << "Activating plugin" << plugin->name();
			emulator = plugin->createContext(engine);
		}
		else
			qWarning() << "Failed to activate plugin" << file;
	}

	if (!emulator)
	{
		qDebug() << "Activating builtin plugin";
		emulator = new DefaultEmulatorContext(engine);
	}
}

void Pico80::quit()
{
	qInfo() << "Stopping";
}

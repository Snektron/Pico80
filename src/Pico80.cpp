#include "Pico80.h"
#include <QDebug>
#include "gui/Logging.h"
#include "DefaultEmulatorContext.h"

Pico80::Pico80():
	emulator(Q_NULLPTR)
{
	Logging::installMessageHandler();
	qInfo() << "Starting";

	manager = new PluginManager();
	pico = new PicoQml(manager);
	engine = new PicoEngine();

	connect(pico, SIGNAL(pluginChanged(QString)), this, SLOT(setEmulatorPlugin(QString)), Qt::QueuedConnection);

	engine->rootContext()->setContextProperty("Pico", pico);
	engine->qmlEngine()->load(QUrl("qrc:/qml/main.qml"));

	emulator = new DefaultEmulatorContext(engine);
}

Pico80::~Pico80()
{
	Logging::removeMessageHandler();
	delete emulator;
	delete engine;
	delete pico;
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

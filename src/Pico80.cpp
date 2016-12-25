#include "Pico80.h"
#include <cstdint>
#include <QThread>
#include "core/Logger.h"
#include "gui/display/Display.h"
#include "gui/LogViewPolicy.h"

#define TAG "Pico80"

Pico80::Pico80(QQmlContext *ctx)
{
	ctx->setContextProperty("LogModel", &logModel);
	Logger::addPolicy(new LogViewPolicy(&logModel));
	Logger::info(TAG, "Starting");

	manager = new PluginManager();
}

void Pico80::initialize(QQmlEngine *engine, QObject *root)
{
	Display *display = root->findChild<Display*>("Display");
	emulator = new EmulatorThread();

	connect(manager, SIGNAL(onPluginChanged(IPlugin*)), display, SLOT(pluginChanged(IPlugin*)), Qt::QueuedConnection);
	connect(manager, SIGNAL(onPluginChanged(IPlugin*)), emulator, SLOT(pluginChanged(IPlugin*)), Qt::QueuedConnection);

	if (manager->hasPlugins())
	{
		IPlugin *plugin = manager->getPlugins()[0];
		manager->setActive(plugin);
	}

	Logger::info(TAG, "Started");
}

Pico80::~Pico80()
{
	delete emulator;
	delete manager;
}

void Pico80::start()
{
	emulator->start();
}

void Pico80::quit()
{
	Logger::info(TAG, "Stopping");
	if (emulator)
		emulator->quit();

	manager->unloadPlugins();
}

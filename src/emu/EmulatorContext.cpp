#include "emu/EmulatorContext.h"

EmulatorContext::EmulatorContext(QQmlEngine &qmlEngine, IPlugin *plugin)
{
	if (plugin)
		plugin->registerPlugin(pluginEngine);

	emulator = new EmulatorThread(&pluginEngine);
}

EmulatorContext::~EmulatorContext()
{
	emulator->quit();
	delete emulator;
}

void EmulatorContext::start()
{
	emulator->start();
}

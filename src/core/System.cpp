#include "core/System.h"

System::System(PluginManager *manager):
	pluginModel(manager)
{
	themeEngine.loadTheme();
	connect(&themeEngine, SIGNAL(themeChanged()), this, SIGNAL(themeChanged()));
}

System::~System()
{
	disconnect(&themeEngine, SIGNAL(themeChanged()), this, SIGNAL(themeChanged()));
}

PicoSettings* System::getSettings()
{
	return &settings;
}

PluginModel* System::getPluginModel()
{
	return &pluginModel;
}

LogModel* System::getLogModel()
{
	return Logging::instance();
}

QVariant System::getTheme()
{
	return themeEngine.getTheme();
}

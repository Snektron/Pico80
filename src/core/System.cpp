#include "core/System.h"
#include <QDebug>

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

void System::setPlugin(QVariant file)
{
	if (!file.isNull())
		emit pluginChanged(file.toString());
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

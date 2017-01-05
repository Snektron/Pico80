#include "core/System.h"
#include <QDebug>

System::System(PluginManager *manager):
	pluginModel(manager)
{}

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

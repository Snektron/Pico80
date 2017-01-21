#include "core/PicoQml.h"
#include <QDebug>

PicoQml::PicoQml(PluginManager *manager):
	pluginModel(manager)
{}

void PicoQml::setPlugin(QVariant file)
{
	if (!file.isNull())
		emit pluginChanged(file.toString());
}

PluginModel* PicoQml::getPluginModel()
{
	return &pluginModel;
}

LogModel* PicoQml::getLogModel()
{
	return Logging::instance();
}

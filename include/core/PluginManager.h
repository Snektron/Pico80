#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>
#include "api/IPlugin.h"

class PluginManager: public QObject
{
	Q_OBJECT
	QList<QString> availablePlugins;
public:
	PluginManager();
	void scanPluginDir();
	QList<QString>* getAvailablePlugins();
};

#endif // PLUGINMANAGER_H

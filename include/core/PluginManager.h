#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>
#include <QString>
#include "Pico80/api/IPlugin.h"

class PluginDescriptor
{
private:
	QString filename, pluginname;

public:
	PluginDescriptor(QString filename, QString pluginname):
		filename(filename), pluginname(pluginname)
	{}

	QString getFileName() { return filename; }
	QString getPluginName() { return pluginname; }
};

class PluginManager: public QObject
{
	Q_OBJECT
public:
	QList<PluginDescriptor> availablePlugins();
	IPlugin* loadPluginByName(QString name);
	IPlugin* loadPluginByFile(QString file);
};

#endif // PLUGINMANAGER_H

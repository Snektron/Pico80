#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>
#include "api/IPlugin.h"

class PluginManager: public QObject
{
	Q_OBJECT
	IPlugin *active;
	QList<IPlugin*> plugins;

public:
	PluginManager();
	~PluginManager();
	bool loadPlugin(QObject *object);
	void reloadPlugins();
	void unloadPlugins();
	bool hasPlugins();
	IPlugin* getPlugin(QString name);
	QList<IPlugin*> getPlugins();

	void setActive(IPlugin* plugin);
	void deactivate();
	IPlugin* getActive();

signals:
	void onPluginChanged(IPlugin *plugin);
};

#endif // PLUGINMANAGER_H

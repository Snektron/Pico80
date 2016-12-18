#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>
#include "api/IPlugin.h"
#include "core/Instance.h"

class PluginManager: public QObject
{
	Q_OBJECT
	Instance *active;
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
	Instance* getActive();

signals:
	void onInstanceChanged(Instance *instance);
};

#endif // PLUGINMANAGER_H

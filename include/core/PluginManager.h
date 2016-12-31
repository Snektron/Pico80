#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>
#include <picore/api/IPlugin.h>

class PluginManager: public QObject
{
	Q_OBJECT
private:
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
};

#endif // PLUGINMANAGER_H

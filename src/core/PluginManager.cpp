#include "core/PluginManager.h"
#include <QApplication>
#include <QDir>
#include <QPluginLoader>
#include <QDebug>

QDir getPluginDirectory()
{
	QDir pluginsDir(QApplication::applicationDirPath());

#if defined(Q_OS_WIN)
	if (pluginsDir.dirName().toLower() == "debug" || pluginsDir.dirName().toLower() == "release")
		pluginsDir.cdUp();
#elif defined(Q_OS_MAC)
	if (pluginsDir.dirName() == "MacOS") {
		pluginsDir.cdUp();
		pluginsDir.cdUp();
		pluginsDir.cdUp();
	}
#endif
	pluginsDir.cd("plugins");

	return pluginsDir;
}

QList<PluginDescriptor> PluginManager::availablePlugins()
{
	QDir pluginsDir = getPluginDirectory();
	QList<PluginDescriptor> plugins;

	foreach (QString fileName, pluginsDir.entryList(QDir::Files))
	{
		QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));

		QObject *instance = loader.instance();
		if (!instance)
			continue;

		IPlugin *plugin = qobject_cast<IPlugin*>(instance);
		if (!plugin)
			continue;

		plugins << PluginDescriptor(fileName, plugin->name());
		delete plugin;
	}

	return plugins;
}

IPlugin* PluginManager::loadPluginByName(QString name)
{
	QDir pluginsDir = getPluginDirectory();

	foreach (QString fileName, pluginsDir.entryList(QDir::Files))
	{
		QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));

		QObject *instance = loader.instance();
		if (!instance)
			continue;

		IPlugin *plugin = qobject_cast<IPlugin*>(instance);
		if (!plugin)
			continue;

		if (plugin->name() == name)
			return plugin;

		delete plugin;
	}

	return Q_NULLPTR;
}

IPlugin* PluginManager::loadPluginByFile(QString file)
{
	QDir pluginsDir = getPluginDirectory();
	QPluginLoader loader(pluginsDir.absoluteFilePath(file));

	QObject *instance = loader.instance();
	if (!instance)
		return Q_NULLPTR;

	return qobject_cast<IPlugin*>(instance);
}

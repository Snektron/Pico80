#include "core/PluginManager.h"
#include <QApplication>
#include <QDir>
#include <QPluginLoader>
#include <QDebug>

PluginManager::PluginManager()
{
	reloadPlugins();
}

PluginManager::~PluginManager()
{
	unloadPlugins();
}

bool PluginManager::loadPlugin(QObject *object)
{
	if (!object)
		return false;

	IPlugin *plugin = qobject_cast<IPlugin*>(object);
	if (!plugin)
		return false;

	qInfo() << "Loaded plugin" << plugin->name();
	plugins.append(plugin);
	return true;
}

void PluginManager::reloadPlugins()
{
	unloadPlugins();

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

	qInfo() << "Searching for plugins...";

	foreach (QString fileName, pluginsDir.entryList(QDir::Files))
	{
		QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
		loadPlugin(loader.instance());
	}
}

void PluginManager::unloadPlugins()
{
	foreach (IPlugin *plugin, plugins)
		delete plugin;

	plugins.clear();
}

bool PluginManager::hasPlugins()
{
	return !plugins.empty();
}

IPlugin* PluginManager::getPlugin(QString name)
{
	foreach(IPlugin *plugin, plugins)
		if (plugin->name() == name)
			return plugin;
	return Q_NULLPTR;
}

QList<IPlugin*> PluginManager::getPlugins()
{
	return plugins;
}

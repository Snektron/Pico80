#include "core/PluginManager.h"
#include <QApplication>
#include <QDir>
#include <QPluginLoader>
#include "core/Logger.h"

#define TAG "PluginManager"

PluginManager::PluginManager():
	active(nullptr)
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

	Logger::info(TAG) << "Loaded plugin '" << plugin->name().toStdString() << "'" << Logger::endl;
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

	Logger::info(TAG, "Searching for plugins");

	foreach (QString fileName, pluginsDir.entryList(QDir::Files))
	{
		QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
		loadPlugin(loader.instance());
	}
}

void PluginManager::unloadPlugins()
{
	foreach (IPlugin *plugin, plugins)
	{
		if (active && active == plugin)
			deactivate();
		delete plugin;
	}

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
	return nullptr;
}

QList<IPlugin*> PluginManager::getPlugins()
{
	return plugins;
}

void PluginManager::setActive(IPlugin *plugin)
{
	if (active)
		deactivate();
	Logger::info(TAG) << "Activating plugin '" << plugin->name().toStdString() << "'" << Logger::endl;
	active = plugin;
	emit onPluginChanged(active);
}

void PluginManager::deactivate()
{
	if (active)
	{
		active = nullptr;
		emit onPluginChanged(nullptr);
	}
}

IPlugin* PluginManager::getActive()
{
	return active;
}

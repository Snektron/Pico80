#include "core/PluginManager.h"
#include <QApplication>
#include <QDir>
#include <QPluginLoader>
#include "core/Logger.h"

#define TAG "PluginManager"

PluginManager::PluginManager()
{
	scanPluginDir();
}

void PluginManager::scanPluginDir()
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

	Logger::info(TAG) << "Searching for plugins in " << pluginsDir.path().toStdString() << Logger::endl;

	foreach (QString fileName, pluginsDir.entryList(QDir::Files))
	{
		QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
		QObject *plugin = loader.instance();
		if (plugin)
			Logger::info(TAG) << "Succesfully loaded plugin " << fileName.toStdString() << Logger::endl;
	}
}

QList<QString>* PluginManager::getAvailablePlugins()
{
	return &availablePlugins;
}

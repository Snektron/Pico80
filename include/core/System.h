#ifndef SYSTEM_H
#define SYSTEM_H

#include <QObject>
#include "core/PluginManager.h"
#include "core/PicoSettings.h"
#include "gui/ThemeEngine.h"
#include "gui/PluginModel.h"
#include "gui/Logging.h"

class System: public QObject
{
	Q_OBJECT
	Q_PROPERTY(PicoSettings *settings READ getSettings CONSTANT)
	Q_PROPERTY(PluginModel *pluginModel READ getPluginModel CONSTANT)
	Q_PROPERTY(LogModel *logModel READ getLogModel CONSTANT)
	Q_PROPERTY(QVariant theme READ getTheme NOTIFY themeChanged)

private:
	PicoSettings settings;
	PluginModel pluginModel;
	ThemeEngine themeEngine;

public:
	System(PluginManager *manager);
	~System();
	PicoSettings* getSettings();
	PluginModel* getPluginModel();
	LogModel* getLogModel();
	QVariant getTheme();

signals:
	themeChanged();
};

#endif // SYSTEM_H

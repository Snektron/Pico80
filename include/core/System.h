#ifndef SYSTEM_H
#define SYSTEM_H

#include <QObject>
#include "core/PluginManager.h"
#include "core/PicoSettings.h"
#include "core/theme/ThemeEngine.h"
#include "gui/PluginModel.h"
#include "gui/Logging.h"

class System: public QObject
{
	Q_OBJECT
	Q_PROPERTY(PicoSettings *settings READ getSettings CONSTANT)
	Q_PROPERTY(PluginModel *pluginModel READ getPluginModel CONSTANT)
	Q_PROPERTY(LogModel *logModel READ getLogModel CONSTANT)

private:
	PicoSettings settings;
	PluginModel pluginModel;

public:
	System(PluginManager *manager);
	Q_INVOKABLE void setPlugin(QVariant file);
	PicoSettings* getSettings();
	PluginModel* getPluginModel();
	LogModel* getLogModel();

signals:
	pluginChanged(QString file);
};

#endif // SYSTEM_H

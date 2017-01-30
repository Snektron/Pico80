#ifndef PICOQML_H
#define PICOQML_H

#include <QObject>
#include "core/PluginManager.h"
#include "core/PicoSettings.h"
#include "gui/PluginModel.h"
#include "gui/Logging.h"

class PicoQml: public QObject
{
	Q_OBJECT
	Q_PROPERTY(PluginModel *pluginModel READ getPluginModel CONSTANT)
	Q_PROPERTY(LogModel *logModel READ getLogModel CONSTANT)

private:
	PluginModel pluginModel;

public:
	PicoQml(PluginManager *manager);
	Q_INVOKABLE void setPlugin(QVariant file);
	PluginModel* getPluginModel();
	LogModel* getLogModel();

signals:
	pluginChanged(QString file);
};

#endif // PICOQML_H

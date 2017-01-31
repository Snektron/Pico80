#ifndef PICOENGINE_H
#define PICOENGINE_H

#include <QObject>
#include <QQmlContext>
#include <QString>
#include <QUrl>
#include "core/PicoQmlEngine.h"
#include "core/PicoSettings.h"
#include "core/PluginManager.h"
#include "core/PicoQml.h"
#include "core/theme/Theme.h"
#include "Pico80/api/IPicoSettings.h"
#include "Pico80/api/IPicoQmlEngine.h"
#include "Pico80/api/ITheme.h"
#include "Pico80/api/IPicoEngine.h"

class PicoEngine: public QObject, public IPicoEngine
{
	Q_OBJECT
private:
	PluginManager mManager;
	PicoQml mPico;
	PicoSettings mSettings;
	Theme mTheme;
	PicoQmlEngine mQmlEngine;

public:
	PicoEngine(QUrl url);
	PluginManager* pluginManager();
	IPicoSettings* settings();
	ITheme* theme();
	IPicoQmlEngine* qmlEngine();
	QQmlContext* rootContext();

private slots:
	void onThemeChanged();

signals:
	void pluginChanged(QString filename);
};

#endif // PICOENGINE_H

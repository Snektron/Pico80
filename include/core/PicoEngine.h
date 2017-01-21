#ifndef PICOENGINE_H
#define PICOENGINE_H

#include <QObject>
#include <QQmlContext>
#include <QString>
#include "core/PicoQmlEngine.h"
#include "core/PicoSettings.h"
#include "core/theme/Theme.h"
#include "Pico80/api/IPicoSettings.h"
#include "Pico80/api/IPicoQmlEngine.h"
#include "Pico80/api/ITheme.h"
#include "Pico80/api/IPicoEngine.h"

class PicoEngine: public QObject, public IPicoEngine
{
	Q_OBJECT
private:
	PicoSettings mSettings;
	Theme mTheme;
	PicoQmlEngine mQmlEngine;

public:
	PicoEngine();
	IPicoSettings* settings();
	ITheme* theme();
	IPicoQmlEngine* qmlEngine();
	QQmlContext* rootContext();

private slots:
	void onThemeChanged();
};

#endif // PICOENGINE_H

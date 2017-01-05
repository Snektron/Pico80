#ifndef PICO80_H
#define PICO80_H

#include <QObject>
#include "core/QmlPicoEngine.h"
#include "core/PluginManager.h"
#include "core/PicoSettings.h"
#include "core/System.h"
#include "gui/PluginModel.h"
#include "emu/EmulatorContext.h"

class Pico80 : public QObject
{
	Q_OBJECT
private:
	QmlPicoEngine *qmlEngine;
	PluginManager *manager;
	EmulatorContext *emulator;
	System *system;
	ThemeEngine *themeEngine;

public:
	Pico80();
	~Pico80();

public slots:
	void setEmulatorPlugin(QString file);
	void quit();

signals:
	void onQuit();
};

#endif // PICO80_H

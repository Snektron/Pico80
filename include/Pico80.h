#ifndef PICO80_H
#define PICO80_H

#include <QObject>
#include "core/PicoQmlEngine.h"
#include "core/PluginManager.h"
#include "core/PicoSettings.h"
#include "core/System.h"
#include "gui/PluginModel.h"
#include "Pico80/api/IEmulatorContext.h"

class Pico80 : public QObject
{
	Q_OBJECT
private:
	PicoQmlEngine *qmlEngine;
	PluginManager *manager;
	System *system;
	ThemeEngine *themeEngine;
	IEmulatorContext *emulator;

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

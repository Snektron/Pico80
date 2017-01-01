#ifndef PICO80_H
#define PICO80_H

#include <QObject>
#include "core/QmlPicoEngine.h"
#include "core/PluginManager.h"
#include "gui/ThemeEngine.h"
#include "emu/EmulatorContext.h"

class Pico80 : public QObject
{
	Q_OBJECT
private:
	QmlPicoEngine qmlEngine;
	ThemeEngine *theme;
	PluginManager *manager;
	EmulatorContext *emulator;

public:
	Pico80();
	~Pico80();

public slots:
	void setEmulatorPlugin(QString file);
	void start();
	void quit();

signals:
	void onQuit();
};

#endif // PICO80_H

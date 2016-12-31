#ifndef PICO80_H
#define PICO80_H

#include <QObject>
#include <QQmlApplicationEngine>
#include "gui/ThemeEngine.h"
#include "core/PluginManager.h"
#include "emu/EmulatorContext.h"

class Pico80 : public QObject
{
	Q_OBJECT
private:
	QQmlApplicationEngine qmlEngine;
	ThemeEngine *theme;
	PluginManager *manager;
	EmulatorContext *emulator;

public:
	Pico80();
	~Pico80();
	template <typename T>
	T findChild(QString name);

public slots:
	void setEmulatorPlugin(QString name);
	void start();
	void quit();

signals:
	void onQuit();
};

#endif // PICO80_H

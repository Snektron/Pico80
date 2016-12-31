#ifndef EMULATORCONTEXT_H
#define EMULATORCONTEXT_H

#include <QObject>
#include <QQmlEngine>
#include <picore/PluginEngine.h>
#include <picore/api/IPlugin.h>
#include "emu/EmulatorThread.h"

class EmulatorContext: public QObject
{
	Q_OBJECT
private:
	PluginEngine pluginEngine;
	EmulatorThread *emulator;

public:
	EmulatorContext(QQmlEngine &qmlEngine, IPlugin *plugin);
	~EmulatorContext();
	void start();
};

#endif // EMULATORCONTEXT_H

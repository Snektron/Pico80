#ifndef EMULATORCONTEXT_H
#define EMULATORCONTEXT_H

#include <QObject>
#include <QQuickItem>
#include <picore/PluginEngine.h>
#include <picore/api/IPlugin.h>
#include "core/QmlPicoEngine.h"
#include "emu/EmulatorThread.h"

class EmulatorContext: public QObject
{
	Q_OBJECT
private:
	PluginEngine pluginEngine;
	EmulatorThread *emulator;
	QQuickItem *display;

public:
	EmulatorContext(QmlPicoEngine &qmlEngine, IPlugin *plugin);
	~EmulatorContext();
	void start();

private:
	void loadDefaults();
	void createQmlComponents(QmlPicoEngine &qmlEngine);
};

#endif // EMULATORCONTEXT_H

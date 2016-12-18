#ifndef PICO80_H
#define PICO80_H

#include <QObject>
#include <QQmlContext>
#include "core/PluginManager.h"
#include "emu/EmulatorThread.h"
#include "gui/LogModel.h"

class Pico80 : public QObject
{
	Q_OBJECT
private:
	LogModel logModel;
	PluginManager *manager;
	EmulatorThread *emulator;

public:
	Pico80(QQmlContext *ctx);
	void initialize(QObject* root);
	~Pico80();

public slots:
	void start();
	void quit();

signals:
	void onQuit();
};

#endif // PICO80_H

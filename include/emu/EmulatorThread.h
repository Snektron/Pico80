#ifndef ASICTHREAD_H
#define ASICTHREAD_H

#include <QThread>
#include "api/IEmulator.h"
#include "api/IPlugin.h"

#define THREAD_INTERVAL 1

class EmulatorWorker : public QObject
{
	Q_OBJECT
private:
	IEmulator *emulator;

public:
	EmulatorWorker();
	~EmulatorWorker();
private slots:
	void tick();
	void pluginChanged(IPlugin *plugin);
};

class EmulatorThread : public QThread
{
	Q_OBJECT
private:

public:
	void run();

public slots:
	void quit();
	void pluginChanged(IPlugin *plugin);

signals:
	void onPluginChanged(IPlugin *plugin);
};

#endif // ASICTHREAD_H

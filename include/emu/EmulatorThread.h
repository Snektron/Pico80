#ifndef ASICTHREAD_H
#define ASICTHREAD_H

#include <QThread>
#include <picore/PluginEngine.h>
#include <picore/api/IEmulator.h>

#define THREAD_INTERVAL 1

class EmulatorWorker : public QObject
{
	Q_OBJECT
private:
	IEmulator *emulator;

public:
	EmulatorWorker(PluginEngine *engine);
	~EmulatorWorker();
private slots:
	void tick();
};

class EmulatorThread : public QThread
{
	Q_OBJECT
private:
	PluginEngine *engine;

public:
	EmulatorThread(PluginEngine *engine);
	void run();

public slots:
	void quit();
};

#endif // ASICTHREAD_H

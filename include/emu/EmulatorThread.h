#ifndef ASICTHREAD_H
#define ASICTHREAD_H

#include <QQuickItem>
#include <QThread>
#include <picore/PluginEngine.h>
#include <picore/api/IEmulator.h>

#define THREAD_INTERVAL 1

class EmulatorWorker : public QObject
{
	Q_OBJECT
private:
	IEmulator *emulator;
	bool initialized;
public:
	EmulatorWorker(PluginEngine *engine);
	~EmulatorWorker();
private slots:
	void tick();
	void onInitialize(QQuickItem *display);
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

signals:
	void initialize(QQuickItem *display);
};

#endif // ASICTHREAD_H

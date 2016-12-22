#ifndef ASICTHREAD_H
#define ASICTHREAD_H

#include <QThread>
#include "api/IEmulator.h"
#include "core/Instance.h"

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
	void instanceChanged(Instance *instance);
};

class EmulatorThread : public QThread
{
	Q_OBJECT
private:

public:
	void run();

public slots:
	void quit();
	void instanceChanged(Instance *instance);

signals:
	void onInstanceChanged(Instance *instance);
};

#endif // ASICTHREAD_H

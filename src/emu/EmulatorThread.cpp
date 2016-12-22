#include "emu/EmulatorThread.h"
#include <cstdint>
#include <QTimer>
#include <QObject>
#include "core/Logger.h"

#define TAG "EmulatorThread"

EmulatorWorker::EmulatorWorker():
	emulator(nullptr)
{}

EmulatorWorker::~EmulatorWorker()
{
	if (emulator)
		delete emulator;
}

void EmulatorWorker::tick()
{
	if (emulator)
		emulator->tick();
}

void EmulatorWorker::instanceChanged(Instance *instance)
{
	if (emulator)
		delete emulator;

	emulator = instance->getPlugin()->createEmulator();

	if (!emulator)
		Logger::warn(TAG, "Failed to instantiate emulator.");
}

void EmulatorThread::run()
{
	QTimer timer;
	timer.setTimerType(Qt::PreciseTimer);
	timer.start(THREAD_INTERVAL);

	EmulatorWorker worker;

	connect(&timer, SIGNAL(timeout()),
			&worker, SLOT(tick()),
			Qt::QueuedConnection);
	connect(this, SIGNAL(onInstanceChanged(Instance*)),
			&worker, SLOT(instanceChanged(Instance*)),
			Qt::QueuedConnection);

	exec();

	disconnect(&timer, SIGNAL(timeout()),
			   &worker, SLOT(tick()));
	disconnect(this, SIGNAL(onInstanceChanged(Instance*)),
			   &worker, SLOT(instanceChanged(Instance*)));
}

void EmulatorThread::quit()
{
	QThread::quit();
	QThread::wait();
}

void EmulatorThread::instanceChanged(Instance *instance)
{
	emit onInstanceChanged(instance);
}

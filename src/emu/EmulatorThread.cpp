#include "emu/EmulatorThread.h"
#include <cstdint>
#include <QTimer>
#include <QObject>
#include "core/Logger.h"

#define TAG "EmulatorThread"

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
		Logger::info(TAG, "Failed to instantiate emulator.");
}

EmulatorWorker::~EmulatorWorker()
{
	if (emulator)
		delete emulator;
}

void EmulatorThread::run()
{
	QTimer timer;
	timer.setTimerType(Qt::PreciseTimer);

	connect(&timer, SIGNAL(timeout()), &asicworker, SLOT(tick()), Qt::QueuedConnection);
	connect(this, SIGNAL(onInstanceChanged(Instance*)), &asicworker, SLOT(instanceChanged(Instance*)), Qt::QueuedConnection);
	timer.start(THREAD_INTERVAL);

	exec();
}

void EmulatorThread::quit()
{
	QThread::quit();
}

void EmulatorThread::instanceChanged(Instance *instance)
{
	Logger::info(TAG, "Test");
	emit onInstanceChanged(instance);
}

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

void EmulatorWorker::pluginChanged(IPlugin *plugin)
{
	if (emulator)
		delete emulator;

	if (plugin)
		emulator = plugin->createEmulator();

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
	connect(this, SIGNAL(onPluginChanged(IPlugin*)),
			&worker, SLOT(pluginChanged(IPlugin*)),
			Qt::QueuedConnection);

	exec();

	disconnect(&timer, SIGNAL(timeout()),
			   &worker, SLOT(tick()));
	disconnect(this, SIGNAL(onPluginChanged(IPlugin*)),
			   &worker, SLOT(pluginChanged(IPlugin*)));
}

void EmulatorThread::quit()
{
	QThread::quit();
	QThread::wait();
}

void EmulatorThread::pluginChanged(IPlugin *plugin)
{
	emit onPluginChanged(plugin);
}

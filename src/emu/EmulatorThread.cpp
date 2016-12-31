#include "emu/EmulatorThread.h"
#include <QTimer>
#include <QObject>
#include <QDebug>

EmulatorWorker::EmulatorWorker(PluginEngine *engine):
	emulator(engine->createEmulator())
{
	if (!emulator)
		qWarning() << "Failed to instantiate emulator";
}

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

EmulatorThread::EmulatorThread(PluginEngine *engine):
	engine(engine)
{}

void EmulatorThread::run()
{
	QTimer timer;
	timer.setTimerType(Qt::PreciseTimer);
	timer.start(THREAD_INTERVAL);

	EmulatorWorker worker(engine);

	connect(&timer, SIGNAL(timeout()),
			&worker, SLOT(tick()),
			Qt::QueuedConnection);

	exec();

	disconnect(&timer, SIGNAL(timeout()),
			   &worker, SLOT(tick()));
}

void EmulatorThread::quit()
{
	QThread::quit();
	QThread::wait();
}

#include "emu/EmulatorThread.h"
#include <QTimer>
#include <QObject>
#include <QDebug>

EmulatorWorker::EmulatorWorker(PluginEngine *engine):
	emulator(engine->createEmulator()),
	initialized(false)
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
	if (emulator && initialized)
		emulator->tick();
}

void EmulatorWorker::onInitialize(QQuickItem *display)
{
	if (emulator)
	{
		emulator->initialize(display);
		initialized = true;
	}
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
			&worker, SLOT(tick()));
	connect(this, SIGNAL(initialize(QQuickItem*)),
			&worker, SLOT(onInitialize(QQuickItem*)),
			Qt::BlockingQueuedConnection);

	exec();
}

void EmulatorThread::quit()
{
	QThread::quit();
	QThread::wait();
}

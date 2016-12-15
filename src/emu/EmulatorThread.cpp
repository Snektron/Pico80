#include "emu/EmulatorThread.h"
#include <cstdint>
#include <QTimer>
#include <QObject>
#include "core/Logger.h"

#define TAG "EmulatorThread"

EmulatorWorker::EmulatorWorker():
	asic(ASIC_CLOCK, ASIC_TIMER)
{
	last = Time::now();
}

void EmulatorWorker::tick()
{
	Time::point time = Time::now();
	Time::nanoseconds passed = time - last;
	last = time;
	int cycles = INSTRUCTIONS(ASIC_CLOCK, Time::toint(passed));
	asic.tick(cycles);
}

Asic* EmulatorWorker::getAsic()
{
	return &asic;
}

void EmulatorThread::run()
{
	QTimer timer;
	timer.setTimerType(Qt::PreciseTimer);

	connect(&timer, SIGNAL(timeout()), &asicworker, SLOT(tick()));
	timer.start(THREAD_INTERVAL);

	exec();
}

Asic* EmulatorThread::getAsic()
{
	if (isRunning())
		throw std::runtime_error("Unsafely tried to access asic.");
	return asicworker.getAsic();
}

void EmulatorThread::quit()
{
	QThread::quit();
}

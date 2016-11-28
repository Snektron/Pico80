#include "emu/AsicThread.h"
#include <cstdint>
#include <QTimer>
#include <QObject>
#include "core/Logger.h"

#define TAG "AsicThread"

AsicWorker::AsicWorker():
	asic(ASIC_CLOCK, ASIC_TIMER)
{
	last = Time::now();
}

void AsicWorker::tick()
{
	Time::point time = Time::now();
	Time::nanoseconds passed = time - last;
	last = time;
	int cycles = INSTRUCTIONS(ASIC_CLOCK, Time::toint(passed));
	asic.tick(cycles);
}

Asic* AsicWorker::getAsic()
{
	return &asic;
}

void AsicThread::run()
{
	QTimer timer;
	timer.setTimerType(Qt::PreciseTimer);

	connect(&timer, SIGNAL(timeout()), &asicworker, SLOT(tick()));
	timer.start(THREAD_INTERVAL);

	exec();
}

Asic* AsicThread::getAsic()
{
	if (isRunning())
		throw std::runtime_error("Unsafely tried to access asic.");
	return asicworker.getAsic();
}

void AsicThread::quit()
{
	QThread::quit();
}

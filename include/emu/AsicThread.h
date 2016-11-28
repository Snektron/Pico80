#ifndef ASICTHREAD_H
#define ASICTHREAD_H

#include <QThread>
#include <memory>
#include <mutex>
#include "emu/Asic.h"
#include "core/Time.h"

#define ASIC_CLOCK MHZ(50)
#define ASIC_TIMER 200
#define THREAD_INTERVAL 1

class AsicWorker : public QObject
{
	Q_OBJECT
private:
	Time::point last;
	Asic asic;

public:
	AsicWorker();
	Asic* getAsic();
private slots:
	void tick();
};

class AsicThread : public QThread
{
	Q_OBJECT
private:
	AsicWorker asicworker;

public:
	void run();
	Asic* getAsic();

public slots:
	void quit();
};

#endif // ASICTHREAD_H

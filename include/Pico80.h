#ifndef PICO80_H
#define PICO80_H

#include <QObject>
#include "emu/AsicThread.h"
#include "gui/Display.h"

class Pico80 : public QObject
{
	Q_OBJECT
private:
	AsicThread asicthread;

public:
	Pico80(Display* display);
	~Pico80();

public slots:
	void start();
	void quit();

signals:
	void onQuit();
};

#endif // PICO80_H

#ifndef PICO80_H
#define PICO80_H

#include <QObject>
#include "emu/AsicThread.h"
class Pico80 : public QObject
{
	Q_OBJECT
private:
	AsicThread asicthread;

public:
	Pico80(QObject* root);
	~Pico80();

public slots:
	void start();
	void quit();

signals:
	void onQuit();
};

#endif // PICO80_H

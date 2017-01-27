#ifndef PICO80_H
#define PICO80_H

#include <QObject>
#include "core/PluginManager.h"
#include "core/PicoEngine.h"
#include "core/PicoQml.h"
#include "Pico80/api/IEmulatorContext.h"

class Pico80 : public QObject
{
	Q_OBJECT
private:
	PicoEngine *engine;
	IEmulatorContext *emulator;

public:
	Pico80();
	~Pico80();

public slots:
	void setEmulatorPlugin(QString file);
	void quit();

signals:
	void onQuit();
};

#endif // PICO80_H

#include "Pico80.h"
#include "core/Logger.h"
#include "gui/Display.h"
#include "emu/Asic.h"
#include "emu/device/Screen.h"

#define TAG "Pico80"

Pico80::Pico80(QObject *root)
{
	Logger::info(TAG, "Starting");
	Display *display = root->findChild<Display*>("Display");
	Asic *asic = asicthread.getAsic();
	connect(asic, SIGNAL(screenDirty(Vram*)), display, SLOT(invalidate(Vram*)), Qt::QueuedConnection);
	connect(display, SIGNAL(turnedOn()), asic, SLOT(intOn()), Qt::QueuedConnection);
}

Pico80::~Pico80()
{
	if (!asicthread.isFinished())
		quit();
}

void Pico80::start()
{
	asicthread.start();
}

void Pico80::quit()
{
	Logger::info(TAG, "Stopping");
	asicthread.quit();
	asicthread.wait();
}

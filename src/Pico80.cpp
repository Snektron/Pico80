#include "Pico80.h"
#include "core/Logger.h"

#define TAG "Pico80"

Pico80::Pico80(Display *display)
{
	Logger::info(TAG, "Starting");
	connect(asicthread.getAsic(), SIGNAL(screenDirty(Vram*)), display, SLOT(invalidate(Vram*)), Qt::QueuedConnection);
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

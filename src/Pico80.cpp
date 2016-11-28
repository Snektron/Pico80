#include "Pico80.h"
#include <cstdint>
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
	connect(display, SIGNAL(keyPress(uint8_t)), asic, SLOT(keyPress(uint8_t)), Qt::QueuedConnection);
	connect(display, SIGNAL(keyRelease(uint8_t)), asic, SLOT(keyRelease(uint8_t)), Qt::QueuedConnection);
	connect(display, SIGNAL(mousePress(uint8_t)), asic, SLOT(mousePress(uint8_t)), Qt::QueuedConnection);
	connect(display, SIGNAL(mouseRelease(uint8_t)), asic, SLOT(mouseRelease(uint8_t)), Qt::QueuedConnection);
	connect(display, SIGNAL(mouseMove(uint8_t, uint8_t)), asic, SLOT(mouseMove(uint8_t, uint8_t)), Qt::QueuedConnection);
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

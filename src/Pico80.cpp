#include "Pico80.h"
#include <cstdint>
#include "core/Logger.h"
#include "gui/Display.h"
#include "emu/pico80/Asic.h"
#include "emu/pico80/device/Screen.h"
#include "gui/LogViewPolicy.h"

#define TAG "Pico80"

Pico80::Pico80(QQmlContext *ctx)
{
	ctx->setContextProperty("LogModel", &logModel);
}

void Pico80::initialize(QObject* root)
{
	Display *display = root->findChild<Display*>("Display");

	Logger::addPolicy(new LogViewPolicy(&logModel));
	Logger::info(TAG, "Starting");
	asicthread = new AsicThread();
	Asic *asic = asicthread->getAsic();
	connect(asic, SIGNAL(screenDirty(Vram*)), display, SLOT(invalidate(Vram*)), Qt::QueuedConnection);
	connect(display, SIGNAL(turnedOn()), asic, SLOT(turnOn()), Qt::QueuedConnection);
	connect(display, SIGNAL(keyPress(uint8_t)), asic, SLOT(keyPress(uint8_t)), Qt::QueuedConnection);
	connect(display, SIGNAL(keyRelease(uint8_t)), asic, SLOT(keyRelease(uint8_t)), Qt::QueuedConnection);
	connect(display, SIGNAL(mousePress(uint8_t)), asic, SLOT(mousePress(uint8_t)), Qt::QueuedConnection);
	connect(display, SIGNAL(mouseRelease(uint8_t)), asic, SLOT(mouseRelease(uint8_t)), Qt::QueuedConnection);
	connect(display, SIGNAL(mouseMove(uint8_t, uint8_t)), asic, SLOT(mouseMove(uint8_t, uint8_t)), Qt::QueuedConnection);
	Logger::info(TAG, "Started");
}

Pico80::~Pico80()
{
	if (!asicthread->isFinished())
		quit();
	delete asicthread;
}

void Pico80::start()
{
	asicthread->start();
}

void Pico80::quit()
{
	Logger::info(TAG, "Stopping");
	asicthread->quit();
	asicthread->wait();
}

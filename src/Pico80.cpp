#include "Pico80.h"
#include <thread>
#include "core/System.h"
#include "core/Logger.h"
#include "core/Graphics.h"
#include "core/Input.h"
#include "core/Time.h"

#define TAG "Pico80"
#define FPS 60

Pico80::Pico80():
	Time::Interval(Time::nanoseconds(SECOND_IN_NANOS / FPS))
{
	System::init("Pico80", 512, 512);

	asic = new Asic();

	Logger::info(TAG, "Started");
}

void Pico80::start()
{
	Interval::start();
}

void Pico80::trigger()
{
	Input::update();

	Graphics::clear();
//	asic->render();
	Graphics::update();

	if (Input::quitRequested())
		stop();
}

void Pico80::stop()
{
	Interval::stop();
}

Pico80::~Pico80()
{
	System::destroy();
	delete asic;
	Logger::info(TAG, "Stopped");
}

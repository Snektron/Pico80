#include "Pico80.h"
#include "core/Logger.h"
#include "core/Graphics.h"
#include "core/Input.h"
#include "core/Time.h"

#define TAG "Pico80"
#define FPS 60

Pico80::Pico80()
{
	Logger::info(TAG, "Starting");

	Time::init();
	Graphics::init(512, 512);

	set_interval(SECOND_IN_NANOS / FPS);

	asic = new Asic();

	Logger::info(TAG, "Started");
}

void Pico80::start()
{
	timer.add(this);
	timer.add(asic);
	timer.add(asic->get_timer_0());
	timer.start();
}

void Pico80::trigger()
{
	Input::update();

	Graphics::clear();
	asic->render();
	Graphics::update();

	if (Input::quitRequested())
		timer.stop();
}

Pico80::~Pico80()
{
	Logger::info(TAG, "Stopping");

	delete asic;

	Graphics::destroy();

	Logger::info(TAG, "Stopped");
}

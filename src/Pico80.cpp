#include "Pico80.h"
#include <thread>
#include <memory>
#include "Settings.h"
#include "core/Logger.h"
#include "core/Graphics.h"
#include "core/Input.h"
#include "core/Time.h"
#include "core/Display.h"
#include "emu/Asic.h"

#define TAG "Pico80"
#define FPS 60

Pico80::Pico80():
	Time::Timer(Time::nanoseconds(SECOND_IN_NANOS / FPS))
{}

bool Pico80::parseArgs(int argc, char* argv[])
{
	return Settings::parse_args(argc, argv);
}

void Pico80::init()
{
	Graphics::init("Pico80", 512, 512);
	Display::init();

	asic = std::make_shared<Asic>();
	Input::Keyboard::setF12Handler(asic);
	Logger::info(TAG, "Started");
}

void Pico80::run()
{
	std::thread asic_thread(&Asic::start, asic.get());

	start();

	asic->stop();
	asic_thread.join();
}

bool Pico80::trigger()
{
	Graphics::clear();
	Input::update();
	Display::render();
	Graphics::update();

	return Input::quit_requested();
}

Pico80::~Pico80()
{
	Logger::info(TAG, "Stopping");
	Input::Keyboard::setF12Handler(NULL);
	Display::destroy();
	Graphics::destroy();
}

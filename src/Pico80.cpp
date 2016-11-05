#include "Pico80.h"
#include <thread>
#include <memory>
#include <cstdint>
#include <sstream>
#include <ctime>
#include <iomanip>
#include "Settings.h"
#include "core/Logger.h"
#include "core/Graphics.h"
#include "core/Input.h"
#include "core/Time.h"
#include "core/Display.h"
#include "emu/Asic.h"

#define TAG "Pico80"

Pico80::Pico80():
	Application(FPS, TPS)
{
	auto t = time(nullptr);
	auto tm = *localtime(&t);

	std::ostringstream oss;
	oss << std::put_time(&tm, "%Y%m%d-%H%M%S.log");
	std::string logfile = oss.str();

	if (Settings::log_to_file())
	{
		if (Settings::quiet())
			Logger::init(new Logger::FilePolicy(logfile));
		else
			Logger::init(new Logger::ConsoleFilePolicy(logfile));
	}else if (!Settings::quiet())
		Logger::init(new Logger::ConsolePolicy());
}

void Pico80::onInitialize()
{
	Graphics::init("Pico80", 512, 512);
	Display::init();

	asic = std::make_shared<Asic>(ASIC_CLOCK, ASIC_TIMER);
	Logger::info(TAG, "Started");

	last = Time::now();
}

void Pico80::onUpdate()
{
	Time::point time = Time::now();
	Time::nanoseconds passed = time - last;
	last = time;
	uint64_t cycles = INSTRUCTIONS(ASIC_CLOCK, Time::toint(passed));
	asic->tick(cycles);
}

void Pico80::onRender()
{
	Graphics::clear();
	Input::update();
	Display::render();
	Graphics::update();

	if (Input::Keyboard::wasF12Pressed())
		asic->f12int();

	if (Input::quit_requested())
		stop();
}

void Pico80::onTerminate()
{
	Logger::info(TAG, "Stopping");
	Display::destroy();
	Graphics::destroy();
}

void Pico80::onError(const std::runtime_error& error)
{
	Logger::error("Runtime error") << error.what() << Logger::endl;
}

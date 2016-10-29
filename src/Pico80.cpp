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
#define CFG "config.cfg"

namespace Pico80
{
	namespace
	{
		Time::TimerWrapper timer(trigger, Time::nanoseconds(SECOND_IN_NANOS / FPS));
		std::unique_ptr<Asic> asic;
	}

	bool parse_args(int argc, char* argv[])
	{
		return Settings::parse_args(argc, argv);
	}

	void init()
	{
		Logger::init(new Logger::ConsolePolicy());
		Logger::info(TAG, "Starting");
		Graphics::init("Pico80", 512, 512);
		Display::init();

		asic = std::make_unique<Asic>();
		Logger::info(TAG, "Started");
	}

	void run()
	{
		std::thread asic_thread(Asic::start, asic.get());

		timer.start();

		asic->stop();
		asic_thread.join();
	}

	bool trigger()
	{
		Graphics::clear();
		Input::update();
		Display::render();
		Graphics::update();

		return Input::quit_requested();
	}

	void destroy()
	{
		Logger::info(TAG, "Stopping");
		Display::destroy();
		Graphics::destroy();
	}
}

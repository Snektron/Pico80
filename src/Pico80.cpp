#include "Pico80.h"
#include <thread>
#include "core/System.h"
#include "core/Logger.h"
#include "core/Graphics.h"
#include "core/Input.h"
#include "core/Time.h"
#include "core/Display.h"
#include "emu/Asic.h"

#define TAG "Pico80"
#define FPS 60

namespace Pico80
{
	namespace
	{
		Time::TimerWrapper timer(trigger, Time::nanoseconds(SECOND_IN_NANOS / FPS));
	}

	void init()
	{
		System::init("Pico80", 512, 512);
		Asic::init();
		Logger::info(TAG, "Started");
	}

	void start()
	{
		std::thread asic(Asic::start);

		timer.start();

		Asic::stop();
		asic.join();
	}

	void stop()
	{
		timer.stop();
	}

	void trigger()
	{
		Graphics::clear();
		Input::update();
		Display::render();
		Graphics::update();

		if (Input::quitRequested())
			stop();
	}

	void destroy()
	{
		Asic::destroy();
		System::destroy();
	}
}

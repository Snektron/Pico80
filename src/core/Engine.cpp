#include "core/Engine.h"
#include <thread>
#include "core/Application.h"
#include "core/Graphics.h"

namespace Engine
{
	namespace
	{
		bool running(false);
		std::shared_ptr<Application> app;
	}

	void initialize()
	{
		WindowConfig wconf = app->getWindowConfig();
		Graphics::init(wconf.name, wconf.width, wconf.height);

		app->onInitialize();
		resize(wconf.width, wconf.height);

		running = true;
	}

	void loop()
	{
		Time::point nextUpdate = Time::now();
		Time::point nextRender = nextUpdate;

		while(running)
		{
			Time::point time = Time::now();

			if (Time::duration(nextUpdate, time) > Time::nanoseconds(MAX_HANG))
				nextUpdate = time;
			if (Time::duration(nextRender, time) > Time::nanoseconds(MAX_HANG))
				nextRender = time;

			while (time >= nextUpdate)
			{
				nextUpdate += app->getTickInterval();
				app->onUpdate();
			}

			while (time >= nextRender)
			{
				nextRender += app->getFrameInterval();
				app->onRender();
				Graphics::update();
			}

			Time::point next = std::min(nextUpdate, nextRender);
			std::this_thread::sleep_until(next);
		}
	}

	void terminate()
	{
		app->onTerminate();
		app.reset();

		Graphics::destroy();
	}

	void setApplication(std::shared_ptr<Application> application)
	{
		if (running)
			throw std::runtime_error("Engine already running.");
		else
			app = application;
	}

	void start()
	{
		if (!app)
			throw std::runtime_error("No application set.");

		try{
			initialize();
			loop();
			terminate();
		}
		catch (const std::runtime_error& error)
		{
			app->onError(error);
		}
	}

	void stop()
	{
		running = false;
	}

	void resize(int width, int height)
	{
		app->onResize(width, height);
	}
}

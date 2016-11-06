#include "core/Application.h"
#include <thread>
#include <algorithm>
#include <exception>
#include "core/Time.h"

Application::Application(int fps, int tps):
	fint(SECOND_IN_NANOS / fps),
	tint(SECOND_IN_NANOS / tps),
	running(false)
{}

void Application::start()
{
	try{
		initialize();
		loop();
		terminate();
	}
	catch (const std::runtime_error& error)
	{
		onError(error);
	}
}

void Application::stop()
{
	running = false;
}

void Application::initialize()
{
	onInitialize();

	running = true;
}

void Application::loop()
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
			nextUpdate += tint;
			onUpdate();
		}

		while (time >= nextRender)
		{
			nextRender += fint;
			onRender();
		}

		Time::point next = std::min(nextUpdate, nextRender);
		std::this_thread::sleep_until(next);
	}
}

void Application::terminate()
{
	onTerminate();
}

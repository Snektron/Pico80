#include <chrono>
#include <cstdint>
#include <thread>
#include "core/Time.h"

using namespace std::chrono;

namespace Time
{

Time::point timestart;

void init()
{
	timestart = high_resolution_clock::now();
}

nanoseconds nanotime()
{
	Time::point now = high_resolution_clock::now();
	return now - timestart;
}

uint64_t nanotoint(nanoseconds nanos)
{
	return duration_cast<nanoseconds>(nanos).count();
}

Timer::Timer():
	running(false)
{}

void Timer::add(TimerCallback* callback)
{
	callbacks.push_back(callback);
	if (running)
	{
		Time::point start = high_resolution_clock::now();
		callback->set_next_trigger(start);
	}
}

void Timer::remove(TimerCallback* callback)
{
	if (next == callback)
		next = nullptr;
	callbacks.remove(callback);
}

void Timer::init()
{
	running = true;
	Time::point start = high_resolution_clock::now();
	for (TimerCallback* cbk : callbacks)
		cbk->set_next_trigger(start);
}

void Timer::start()
{
	init();

	while(running)
	{
		if (next != nullptr)
		{
			next->trigger();
			nanoseconds interval = next->get_interval();
			next->set_next_trigger(high_resolution_clock::now() + interval);
		}

		Time::point next_trigger = Time::point::max();

		for (TimerCallback* cbk : callbacks)
		{
			if (cbk->get_next_trigger() < next_trigger)
			{
				next_trigger = cbk->get_next_trigger();
				next = cbk;
			}
		}

		if (next_trigger == Time::point::max() || callbacks.size() == 0)
			break; // sanity check / no callbacks left
		if (next_trigger < high_resolution_clock::now())
			continue;
		else
			std::this_thread::sleep_until(next_trigger);
	}

	running = false;
}

void Timer::stop()
{
	running = false;
}

}

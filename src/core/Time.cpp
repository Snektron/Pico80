#include <chrono>
#include <cstdint>
#include <thread>
#include "core/Time.h"

using namespace std::chrono;

namespace Time
{
	point now()
	{
		return high_resolution_clock::now();
	}

	uint64_t toint(nanoseconds nanos)
	{
		return duration_cast<nanoseconds>(nanos).count();
	}

	Interval::Interval(nanoseconds interval):
			running(false),
			interval(interval)
	{}

	void Interval::start()
	{
		running = true;

		while(running)
		{
			Time::point start = now();
			trigger();
			Time::point stop = now();
			Time::point next = start + interval;
			if (next > stop)
				std::this_thread::sleep_until(next);
		}
	}

	void Interval::stop()
	{
		running = false;
	}

	void Interval::set_interval(nanoseconds interval)
	{
		this->interval = interval;
	}

	nanoseconds Interval::get_interval()
	{
		return interval;
	}
}

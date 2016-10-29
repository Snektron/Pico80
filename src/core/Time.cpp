#include "core/Time.h"
#include <chrono>
#include <cstdint>
#include <thread>
#include <atomic>

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

	Timer::Timer(nanoseconds interval):
			running(false),
			interval(interval)
	{}

	void Timer::start()
	{
		running = true;

		while(running)
		{
			Time::point start = now();
			if (trigger())
			{
				stop();
				break;
			}
			Time::point stop = now();
			Time::point next = start + interval;
			if (next > stop)
				std::this_thread::sleep_until(next);
		}
	}

	void Timer::stop()
	{
		running = false;
	}

	void Timer::set_interval(nanoseconds interval)
	{
		this->interval = interval;
	}

	nanoseconds Timer::get_interval()
	{
		return interval;
	}

	TimerWrapper::TimerWrapper(const std::function<bool()> callback, nanoseconds interval):
			Timer(interval),
			callback(callback)
	{}

	bool TimerWrapper::trigger()
	{
		return callback();
	}
}

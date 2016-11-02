#include "core/Time.h"
#include <chrono>
#include <cstdint>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include "core/Logger.h"

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

	nanoseconds duration(point start, point end)
	{
		return duration_cast<nanoseconds>(end - start);
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
				break;
			Time::point stop = now();
			Time::point next = start + interval;
			if (next > stop)
				std::this_thread::sleep_until(next);
		}

		running = false;
	}

	void Timer::stop()
	{
		running = false;
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

#ifndef INCLUDE_CORE_TIME_H_
#define INCLUDE_CORE_TIME_H_

#include <cstdint>
#include <list>
#include <chrono>

#define SECOND_IN_NANOS (1000000000)

namespace Time
{
	using std::chrono::nanoseconds;

	typedef std::chrono::time_point<std::chrono::high_resolution_clock> point;

	void init();

	nanoseconds nanotime();

	uint64_t nanotoint(nanoseconds nanos);

	class TimerCallback
	{
	private:
		Time::point next_trigger;
		nanoseconds interval;

	public:
		virtual void trigger() = 0;
		virtual ~TimerCallback() = default;

		void set_interval(uint64_t newinterval)
		{
			interval = nanoseconds(newinterval);
		}

		nanoseconds get_interval()
		{
			return interval;
		}

		void set_next_trigger(Time::point next)
		{
			next_trigger = next;
		}

		Time::point get_next_trigger()
		{
			return next_trigger;
		}
	};

	class Timer
	{
	private:
		bool running;
		std::list<TimerCallback*> callbacks;
		TimerCallback* next = nullptr;

		void init();
	public:
		Timer();
		void add(TimerCallback* callback);
		void remove(TimerCallback* callback);
		void start();
		void stop();
	};
}

#endif /* INCLUDE_CORE_TIME_H_ */

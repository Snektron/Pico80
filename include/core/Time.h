#ifndef INCLUDE_CORE_TIME_H_
#define INCLUDE_CORE_TIME_H_

#include <cstdint>
#include <list>
#include <chrono>
#include <atomic>
#include <functional>

#define SECOND_IN_NANOS (1000000000ull)

namespace Time
{
	using std::chrono::nanoseconds;

	typedef std::chrono::time_point<std::chrono::high_resolution_clock> point;

	void init();

	point now();

	uint64_t toint(nanoseconds nanos);

	class Timer
	{
	private:
		std::atomic<bool> running;
		nanoseconds interval;

	public:
		Timer(nanoseconds interval);
		void start();
		void stop();
		virtual void trigger() = 0;
		void set_interval(nanoseconds interval);
		nanoseconds get_interval();
		virtual ~Timer() = default;
	};

	class TimerWrapper : public Timer
	{
	private:
		std::function<void()> callback;

	public:
		TimerWrapper(const std::function<void()> callback, nanoseconds interval);
		void trigger();
	};
}

#endif /* INCLUDE_CORE_TIME_H_ */

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
		void set_interval(nanoseconds interval);
		nanoseconds get_interval();

		virtual bool trigger() = 0;
		virtual ~Timer() = default;
	};

	class TimerWrapper : public Timer
	{
	private:
		std::function<bool()> callback;

	public:
		TimerWrapper(const std::function<bool()> callback, nanoseconds interval);
		bool trigger();
	};
}

#endif /* INCLUDE_CORE_TIME_H_ */

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

	uint64_t toint(nanoseconds nanos);

	class Interval
	{
	private:
		bool running;
		nanoseconds interval;

	public:
		Interval(nanoseconds interval);
		void start();
		void stop();
		virtual void trigger() = 0;
		void set_interval(nanoseconds interval);
		nanoseconds get_interval();
		virtual ~Interval() = default;
	};
}

#endif /* INCLUDE_CORE_TIME_H_ */

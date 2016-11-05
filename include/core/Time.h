#ifndef INCLUDE_CORE_TIME_H_
#define INCLUDE_CORE_TIME_H_

#include <cstdint>
#include <chrono>

#define SECOND_IN_NANOS (1000000000ull)

namespace Time
{
	using std::chrono::nanoseconds;

	typedef std::chrono::time_point<std::chrono::high_resolution_clock> point;

	point now();
	nanoseconds duration(point start, point end);
	uint64_t toint(nanoseconds nanos);
	uint64_t secondsSince1997();
}

#endif /* INCLUDE_CORE_TIME_H_ */

#ifndef INCLUDE_PICO80_H_
#define INCLUDE_PICO80_H_

#include "core/Time.h"
#include "emu/Asic.h"

class Pico80 : Time::TimerCallback
{
private:
	Time::Timer timer;
	Asic* asic;

public:
	Pico80();

	void start();

	void trigger();

	~Pico80();
};

#endif /* INCLUDE_PICO80_H_ */

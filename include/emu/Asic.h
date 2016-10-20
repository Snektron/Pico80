#ifndef INCLUDE_EMU_ASIC_H_
#define INCLUDE_EMU_ASIC_H_

#include "interrupt/TimerInt.h"

#define MHZ(x) (x * 1000000)

#define CLOCK_RATE MHZ(50)
#define CLOCK_FREQ 500

#define TIMER_FREQ 1

namespace Asic
{
	void init();

	void start();
	void stop();
	void trigger();

	void set_interrupt();
	void reset_interrupt();

	void destroy();
}

#endif /* INCLUDE_EMU_ASIC_H_ */

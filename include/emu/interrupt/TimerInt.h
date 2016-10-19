#ifndef INCLUDE_EMU_INTERRUPT_TIMERINT_H_
#define INCLUDE_EMU_INTERRUPT_TIMERINT_H_

#include <cstdint>
#include "emu/interrupt/Interrupt.h"
#include "core/Time.h"
#include "core/Logger.h"

class TimerInt : public InterruptDevice, public Time::Interval
{
public:
	TimerInt(Interrupt *interrupt, int index, Time::nanoseconds interval):
		InterruptDevice(interrupt, index),
		Time::Interval(interval)
	{}

	void trigger()
	{
		InterruptDevice::trigger();
	}
};

#endif /* INCLUDE_EMU_INTERRUPT_TIMERINT_H_ */

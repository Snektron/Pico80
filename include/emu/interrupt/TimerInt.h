#ifndef INCLUDE_EMU_INTERRUPT_TIMERINT_H_
#define INCLUDE_EMU_INTERRUPT_TIMERINT_H_

#include <cstdint>
#include "emu/interrupt/Interrupt.h"
#include "core/Logger.h"

class TimerInt : public InterruptDevice
{
private:
	uint64_t interval; // trigger interval, in instructions
	uint64_t left;

public:
	TimerInt(Interrupt *interrupt, int index, uint64_t interval):
		InterruptDevice(interrupt, index),
		interval(interval),
		left(interval)
	{
		Logger::debug("Timer int") << "Timer Interrupt period: " << interval << " cycles" << Logger::endl;
	}

	void update(uint64_t executed)
	{
		left -= executed <= left ? executed : 0;
	}

	// return number of instructions left until
	// the timer should trigger
	uint64_t instructions_to_trigger()
	{
		return left;
	}

	void trigger()
	{
		left = interval;
		InterruptDevice::trigger();
	}
};

#endif /* INCLUDE_EMU_INTERRUPT_TIMERINT_H_ */

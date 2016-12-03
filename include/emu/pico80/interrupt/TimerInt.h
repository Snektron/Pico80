#ifndef INCLUDE_EMU_INTERRUPT_TIMERINT_H_
#define INCLUDE_EMU_INTERRUPT_TIMERINT_H_

#include <memory>
#include "emu/pico80/interrupt/Interrupt.h"
#include "core/Logger.h"

class TimerInt : public InterruptDevice
{
private:
	int interval; // trigger interval, in instructions
	int left;

public:
	TimerInt(std::shared_ptr<Interrupt> interrupt, int index, int interval):
		InterruptDevice(interrupt, index),
		interval(interval),
		left(interval)
	{}

	void update(int executed)
	{
		left -= executed <= left ? executed : 0;
	}

	// return number of instructions left until
	// the timer should trigger
	int instructions_to_trigger()
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

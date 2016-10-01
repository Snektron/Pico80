#ifndef INCLUDE_EMU_INTERRUPT_TIMERINT_H_
#define INCLUDE_EMU_INTERRUPT_TIMERINT_H_

#include <cstdint>
#include "emu/interrupt/Interrupt.h"
#include "core/Time.h"
#include "core/Logger.h"

class TimerInt : public InterruptDevice, public Time::TimerCallback
{
public:
	TimerInt(Interrupt *interrupt, int index, uint64_t interval):
		InterruptDevice(interrupt, index)
	{
		set_interval(interval);
	}

	void trigger()
	{
		InterruptDevice::trigger();
	}
};

#endif /* INCLUDE_EMU_INTERRUPT_TIMERINT_H_ */

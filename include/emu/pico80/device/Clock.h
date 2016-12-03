#ifndef INCLUDE_EMU_DEVICE_CLOCK_H_
#define INCLUDE_EMU_DEVICE_CLOCK_H_

#include "z80e/z80e.h"

class ClockReg : public Z80e::ReadonlyIODevice
{
private:
	int index;

public:
	ClockReg(int index):
		index(index)
	{}

	uint8_t read()
	{
		return (uint8_t) (Time::secondsSince1997() >> index * 8 & 0xFF);
	}
};

#endif /* INCLUDE_EMU_DEVICE_CLOCK_H_ */

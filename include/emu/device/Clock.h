#ifndef INCLUDE_EMU_DEVICE_CLOCK_H_
#define INCLUDE_EMU_DEVICE_CLOCK_H_

#include "z80e/z80e.h"

class ClockReg : public Z80e::ReadonlyIODevice
{
private:
	int byte;

public:
	ClockReg(int byte);
	uint8_t read();
};

#endif /* INCLUDE_EMU_DEVICE_CLOCK_H_ */

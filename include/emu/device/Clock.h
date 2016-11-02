#ifndef INCLUDE_EMU_DEVICE_CLOCK_H_
#define INCLUDE_EMU_DEVICE_CLOCK_H_

#include "z80e/z80e.h"

class ClockReg : public Z80e::IODevice
{
private:
	int byte;

public:
	ClockReg(int byte);
	uint8_t read();
	void write(uint8_t value);
};

#endif /* INCLUDE_EMU_DEVICE_CLOCK_H_ */

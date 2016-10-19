#ifndef INCLUDE_EMU_DEVICE_INTERRUPT_H_
#define INCLUDE_EMU_DEVICE_INTERRUPT_H_

#include <cstdint>
#include "z80e/z80e.h"
#include "core/Time.h"

class Interrupt : public Z80e::BasicIODevice
{
private:
	Z80e::BasicIODevice mask;

public:
	void set_enabled(int index, bool enabled);
	bool is_enabled(int index);
	void trigger(int index);
	void write(uint8_t value);
	Z80e::BasicIODevice* get_interrupt_mask();
};

class InterruptDevice
{
private:
	Interrupt *interrupt;
	int index;
public:
	InterruptDevice(Interrupt *interrupt, int index):
		interrupt(interrupt),
		index(index)
	{}

	void trigger()
	{
		interrupt->trigger(index);
	}

	bool is_enabled()
	{
		return interrupt->is_enabled(index);
	}
};

#endif /* INCLUDE_EMU_DEVICE_INTERRUPT_H_ */

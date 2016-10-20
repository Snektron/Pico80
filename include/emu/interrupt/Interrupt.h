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
	void set_enabled(int pin, bool enabled);
	bool is_enabled(int pin);
	void trigger(int pin);
	void write(uint8_t value);
	Z80e::BasicIODevice* get_interrupt_mask();
};

class InterruptDevice
{
private:
	Interrupt *owner;
	int index;
public:
	InterruptDevice(Interrupt *owner, int index):
		owner(owner),
		index(index)
	{}

	void trigger()
	{
		if (owner)
			owner->trigger(index);
	}

	bool is_enabled()
	{
		if (!owner)
			return false;
		return owner->is_enabled(index);
	}
};

#endif /* INCLUDE_EMU_DEVICE_INTERRUPT_H_ */

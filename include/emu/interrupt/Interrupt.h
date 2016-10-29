#ifndef INCLUDE_EMU_DEVICE_INTERRUPT_H_
#define INCLUDE_EMU_DEVICE_INTERRUPT_H_

#include <cstdint>
#include <memory>
#include "z80e/z80e.h"
#include "core/Time.h"

class Interrupt : public Z80e::BasicIODevice
{
private:
	std::shared_ptr<Z80e::BasicIODevice> mask;
	std::shared_ptr<Z80e::CPU> cpu;

public:
	Interrupt(std::shared_ptr<Z80e::CPU> cpu);
	void set_enabled(int pin, bool enabled);
	bool is_enabled(int pin);
	void trigger(int pin);
	void write(uint8_t value);
	std::shared_ptr<Z80e::BasicIODevice> get_interrupt_mask();
};

class InterruptDevice
{
private:
	std::shared_ptr<Interrupt> owner;
	int index;
public:
	InterruptDevice(std::shared_ptr<Interrupt> owner, int index):
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

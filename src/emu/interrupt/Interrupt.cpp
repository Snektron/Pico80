#include <cstdint>
#include "emu/interrupt/Interrupt.h"
#include "emu/Asic.h"
#include "core/Logger.h"

#define TAG "Interrupt"

Interrupt::Interrupt(Asic *asic):
	asic(asic)
{}

void check_index(int& index)
{
	if (index < 0 || index > 8)
	{
		Logger::warn(TAG) << "Interrupt out of range: " << index << Logger::endl;
		Logger::warn(TAG, "Falling back to index 0");
		index = 0;
	}
}

void Interrupt::set_enabled(int index, bool enabled)
{
	check_index(index);
	uint8_t enable_mask = mask.read();

	if (enabled)
		enable_mask |= 1 << index;
	else
		enable_mask &= ~(1 << index);

	mask.write(enable_mask);
}

bool Interrupt::is_enabled(int index)
{
	check_index(index);
	return mask.read() & (1 << index);
}

void Interrupt::trigger(int index)
{
	check_index(index);

	if (is_enabled(index))
	{
		asic->set_interrupt();
		uint8_t trigger_mask = Z80e::BasicIODevice::read();
		trigger_mask |= 1 << index;
		Z80e::BasicIODevice::write(trigger_mask);
	}
}

void Interrupt::write(uint8_t value)
{
	if (!value) // if all interrupts are acknowleged, stop interrupting.
		asic->reset_interrupt();
	Z80e::BasicIODevice::write(value);
}

Z80e::BasicIODevice* Interrupt::get_interrupt_mask()
{
	return &mask;
}

#include <cstdint>
#include "emu/interrupt/Interrupt.h"
#include "emu/Asic.h"
#include "core/Logger.h"

#define TAG "Interrupt"

bool check_pin(int pin)
{
	if (pin < 0 || pin > 8)
	{
		Logger::warn(TAG) << "Interrupt out of range: " << pin << Logger::endl;
		return false;
	}

	return true;
}

void Interrupt::set_enabled(int pin, bool enabled)
{
	if (!check_pin(pin))
		return;

	uint8_t enable_mask = mask.read();

	if (enabled)
		enable_mask |= 1 << pin;
	else
		enable_mask &= ~(1 << pin);

	mask.write(enable_mask);
}

bool Interrupt::is_enabled(int pin)
{
	if (!check_pin(pin))
		return false;
	return mask.read() & (1 << pin);
}

void Interrupt::trigger(int pin)
{
	if (is_enabled(pin))
	{
		Asic::set_interrupt();
		uint8_t trigger_mask = Z80e::BasicIODevice::read();
		trigger_mask |= 1 << pin;
		Z80e::BasicIODevice::write(trigger_mask);
	}
}

void Interrupt::write(uint8_t value)
{
	if (!value) // if all interrupts are acknowleged, stop interrupting.
		Asic::reset_interrupt();
	Z80e::BasicIODevice::write(value);
}

Z80e::BasicIODevice* Interrupt::get_interrupt_mask()
{
	return &mask;
}

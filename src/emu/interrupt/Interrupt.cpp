#include "emu/interrupt/Interrupt.h"
#include <cstdint>
#include <atomic>
#include <mutex>
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

Interrupt::Interrupt():
	trig(new Z80e::ReadonlyIODevice()),
	interrupting(false)
{}

void Interrupt::set_enabled(int pin, bool enabled)
{
	std::lock_guard<std::mutex> lock();
	if (!check_pin(pin))
		return;

	uint8_t enable_mask = Z80e::BasicIODevice::read();

	if (enabled)
		enable_mask |= 1 << pin;
	else
		enable_mask &= ~(1 << pin);

	Z80e::BasicIODevice::write(enable_mask);
}

bool Interrupt::is_enabled(int pin)
{
	std::lock_guard<std::mutex> lock();
	if (!check_pin(pin))
		return false;
	return Z80e::BasicIODevice::read() & (1 << pin);
}

void Interrupt::trigger(int pin)
{
	std::lock_guard<std::mutex> lock();
	if (is_enabled(pin))
	{
		interrupting = 1;
		uint8_t trigger_mask = trig->read();
		trigger_mask |= 1 << pin;
		trig->set_value(trigger_mask);
	}
}

void Interrupt::write(uint8_t value)
{
	std::lock_guard<std::mutex> lock();
	uint8_t trigger_mask = value & trig->read(); // only disable pins
	trig->set_value(trigger_mask); // disable interrupt trigs
	if (!trigger_mask) // if all interrupts are acknowleged, stop interrupting.
		interrupting = 0;
	Z80e::BasicIODevice::write(value);
}

bool Interrupt::is_interrupting()
{
	return interrupting.load();
}

std::shared_ptr<Z80e::ReadonlyIODevice> Interrupt::get_interrupt_trig()
{
	return trig; // TODO make thread-safe
}

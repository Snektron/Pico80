#include "emu/device/Interrupt.h"
#include "emu/Asic.h"
#include "core/Logger.h"

InterruptDevice::InterruptDevice(Interrupt *interrupt):
	interrupt(interrupt),
	enabled(false)
{}

void InterruptDevice::trigger()
{

}

void InterruptDevice::set_enabled(bool enabled)
{
	this->enabled = enabled;
}

bool InterruptDevice::is_enabled()
{
	return enabled;
}

Interrupt::Interrupt(Asic *asic):
	asic(asic)
{}

void Interrupt::set_device(int index, InterruptDevice* device)
{
	devices[index % 8] = device;
}

InterruptDevice* Interrupt::get_device(int index)
{
	return devices[index % 8];
}

void Interrupt::trigger(InterruptDevice* device)
{
	if (device && device->is_enabled())
	{
		asic->interrupt();
	}
}

void Interrupt::trigger(int index)
{
	trigger(get_device(index));
}

Z80e::BasicIODevice* Interrupt::get_interrupt_mask()
{
	return &mask;
}

Z80e::BasicIODevice* Interrupt::get_interrupt_enable()
{
	return &enable;
}

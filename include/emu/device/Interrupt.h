#ifndef INCLUDE_EMU_DEVICE_INTERRUPT_H_
#define INCLUDE_EMU_DEVICE_INTERRUPT_H_

#include <vector>
#include "z80e/z80e.h"
#include "core/Time.h"

class Asic;
class Interrupt;

class InterruptDevice
{
private:
	Interrupt *interrupt;
	bool enabled;

public:
	InterruptDevice(Interrupt *interrupt);
	void trigger();
	void set_enabled(bool enabled);
	bool is_enabled();
	virtual ~InterruptDevice() = default;
};

class Interrupt
{
private:
	Asic *asic;
	Z80e::BasicIODevice mask, enable;
	InterruptDevice* devices[8];

public:
	Interrupt(Asic *asic);
	void set_device(int index, InterruptDevice* device);
	InterruptDevice* get_device(int index);
	void trigger(InterruptDevice* device);
	void trigger(int index);
	Z80e::BasicIODevice* get_interrupt_mask();
	Z80e::BasicIODevice* get_interrupt_enable();
};

#endif /* INCLUDE_EMU_DEVICE_INTERRUPT_H_ */

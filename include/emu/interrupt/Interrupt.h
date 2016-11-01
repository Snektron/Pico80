#ifndef INCLUDE_EMU_DEVICE_INTERRUPT_H_
#define INCLUDE_EMU_DEVICE_INTERRUPT_H_

#include <cstdint>
#include <memory>
#include <atomic>
#include <mutex>
#include "z80e/z80e.h"
#include "core/Time.h"

	class TrigIODevice : public Z80e::IODevice
	{
	private:
		std::atomic<uint8_t> portvalue;
	public:
		uint8_t read()
		{
			return portvalue;
		}

		void write(uint8_t value)
		{}

		void set_value(uint8_t value)
		{
			portvalue = value;
		}
	};

class Interrupt : public Z80e::BasicIODevice, public Z80e::InterruptController
{
private:
	std::shared_ptr<TrigIODevice> trig;
	bool interrupting;
	std::mutex lock;

public:
	Interrupt();
	void set_enabled(int pin, bool enabled);
	bool is_enabled(int pin);
	void trigger(int pin);
	void write(uint8_t value);
	bool is_interrupting();
	std::shared_ptr<TrigIODevice> get_interrupt_trig();
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

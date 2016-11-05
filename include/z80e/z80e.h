#ifndef INCLUDE_Z80E_Z80E_H_
#define INCLUDE_Z80E_Z80E_H_

#include <cstdint>
#include <memory>
#include <atomic>
extern "C"
{
#include "z80e/core/cpu.h"
}
#include "z80e/core/Memory.h"
#include "z80e/core/Device.h"
#include "z80e/core/Interrupt.h"

namespace Z80e
{
	class CPU
	{
	private:
		std::unique_ptr<z80cpu_t, void(*)(z80cpu_t*)> z80;
		std::shared_ptr<Memory> mem;
		std::shared_ptr<InterruptController> ictrl;
		std::shared_ptr<IODevice> devices[0x100];

	public:
		CPU(std::shared_ptr<Memory> mem, std::shared_ptr<InterruptController> ictrl):
			z80(cpu_init(), cpu_free),
			ictrl(ictrl),
			mem(mem)
		{
			z80iodevice_t device = {nullptr, &IODevice::io_read, &IODevice::io_write};
			for (int i = 0; i < 0x100; i++)
				z80->devices[i] = device;
			z80->memory = mem.get();
			z80->read_byte = &Memory::mem_read;
			z80->write_byte = &Memory::mem_write;
			z80->interrupt = ictrl.get();
			z80->interrupting = &InterruptController::interrupting;
		}

		void add_device(uint8_t port, std::shared_ptr<IODevice> device)
		{
			z80->devices[port].device = device.get();
			devices[port] = device;
		}

		void rem_device(uint8_t port)
		{
			z80->devices[port].device = nullptr;
		}

		uint8_t read_register_byte(registers reg_to_read)
		{
			return cpu_read_register_byte(z80.get(), reg_to_read);
		}

		uint16_t read_register_word(registers reg_to_read)
		{
			return cpu_read_register_word(z80.get(), reg_to_read);
		}

		uint8_t write_register_byte(registers reg_to_write, uint8_t value)
		{
			return cpu_write_register_byte(z80.get(), reg_to_write, value);
		}

		uint16_t write_register_word(registers reg_to_write, uint16_t value)
		{
			return cpu_write_register_word(z80.get(), reg_to_write, value);
		}

		uint8_t read_byte(uint16_t address)
		{
			return cpu_read_byte(z80.get(), address);
		}

		void write_byte(uint16_t address, uint8_t value)
		{
			cpu_write_byte(z80.get(), address, value);
		}

		uint16_t read_word(uint16_t address)
		{
			return cpu_read_word(z80.get(), address);
		}

		void write_word(uint16_t address, uint16_t value)
		{
			cpu_write_word(z80.get(), address, value);
		}

		int execute(int cycles)
		{
			return cpu_execute(z80.get(), cycles);
		}
	};
}
#endif /* INCLUDE_Z80E_Z80E_H_ */

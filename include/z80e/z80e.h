#ifndef INCLUDE_Z80E_Z80E_H_
#define INCLUDE_Z80E_Z80E_H_

#include <cstdint>
#include <memory>
#include <atomic>
#include "z80e/core/cpu.h"
#include "z80e/core/Memory.h"
#include "z80e/core/Device.h"
#include "z80e/core/Interrupt.h"

namespace Z80e
{
	class CPU
	{
	private:
		std::unique_ptr<z80cpu_t, void(*)(z80cpu_t*)> cpu;
		std::shared_ptr<Memory> mem;
		std::shared_ptr<InterruptController> ictrl;
		std::shared_ptr<IODevice> devices[0x100];

	public:
		CPU(std::shared_ptr<Memory> mem, std::shared_ptr<InterruptController> ictrl):
			cpu(cpu_init(), cpu_free),
			ictrl(ictrl),
			mem(mem)
		{
			z80iodevice_t device = {nullptr, &IODevice::io_read, &IODevice::io_write};
			for (int i = 0; i < 0x100; i++)
				cpu->devices[i] = device;
			cpu->memory = mem.get();
			cpu->read_byte = &Memory::mem_read;
			cpu->write_byte = &Memory::mem_write;
			cpu->interrupt = ictrl.get();
			cpu->interrupting = &InterruptController::interrupting;
		}

		void add_device(uint8_t port, std::shared_ptr<IODevice> device)
		{
			cpu->devices[port].device = device.get();
			devices[port] = device;
		}

		void rem_device(uint8_t port)
		{
			cpu->devices[port].device = nullptr;
		}

		uint8_t read_register_byte(registers reg_to_read)
		{
			return cpu_read_register_byte(cpu.get(), reg_to_read);
		}

		uint16_t read_register_word(registers reg_to_read)
		{
			return cpu_read_register_word(cpu.get(), reg_to_read);
		}

		uint8_t write_register_byte(registers reg_to_write, uint8_t value)
		{
			return cpu_write_register_byte(cpu.get(), reg_to_write, value);
		}

		uint16_t write_register_word(registers reg_to_write, uint16_t value)
		{
			return cpu_write_register_word(cpu.get(), reg_to_write, value);
		}

		uint8_t read_byte(uint16_t address)
		{
			return cpu_read_byte(cpu.get(), address);
		}

		void write_byte(uint16_t address, uint8_t value)
		{
			cpu_write_byte(cpu.get(), address, value);
		}

		uint16_t read_word(uint16_t address)
		{
			return cpu_read_word(cpu.get(), address);
		}

		void write_word(uint16_t address, uint16_t value)
		{
			cpu_write_word(cpu.get(), address, value);
		}

		int execute(int cycles)
		{
			return cpu_execute(cpu.get(), cycles);
		}
	};
}
#endif /* INCLUDE_Z80E_Z80E_H_ */

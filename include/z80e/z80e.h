#ifndef INCLUDE_Z80E_Z80E_H_
#define INCLUDE_Z80E_Z80E_H_

#include <stdint.h>
extern "C"
{
#include "z80e/cpu.h"
}

namespace Z80e
{
	uint8_t z80e_io_read(void *device);
	void z80e_io_write(void *device, uint8_t value);

	class Memory
	{
	public:
		static uint8_t mem_read(void *memptr, uint16_t address)
		{
			Memory *memory = (Memory*) memptr;
			if (memory)
				return memory->read(address);
			return 0;
		}

		static void mem_write(void *memptr, uint16_t address, uint8_t value)
		{
			Memory *memory = (Memory*) memptr;
			if (memory)
				memory->write(address, value);
		}

		virtual uint8_t read(uint16_t address) = 0;
		virtual void write(uint16_t address, uint8_t value) = 0;
		virtual ~Memory() = default;
	};

	class IODevice
	{
	public:
		static uint8_t io_read(void *devptr)
		{
			IODevice *device = (IODevice*) devptr;
			if (device)
				return device->read();
			return 0;
		}

		static void io_write(void *devptr, uint8_t value)
		{
			IODevice *device = (IODevice*) devptr;
			if (device)
				device->write(value);
		}

		virtual uint8_t read() = 0;
		virtual void write(uint8_t value) = 0;
		virtual ~IODevice() = default;
	};

	class BasicIODevice : public IODevice
	{
	private:
		uint8_t portvalue;
	public:
		uint8_t read()
		{
			return portvalue;
		}

		void write(uint8_t value)
		{
			portvalue = value;
		}
	};

	class CPU
	{
	private:
		z80cpu_t* z80;

	public:
		CPU(Memory *mem)
		{
			z80 = cpu_init();
			z80iodevice_t device = {nullptr, &IODevice::io_read, &IODevice::io_write};
			for (int i = 0; i < 0x100; i++)
				z80->devices[i] = device;
			z80->memory = mem;
			z80->read_byte = &Memory::mem_read;
			z80->write_byte = &Memory::mem_write;
		}

		void add_device(uint8_t port, IODevice* device)
		{
			z80->devices[port].device = device;
		}

		void rem_device(uint8_t port)
		{
			z80->devices[port].device = nullptr;
		}

		uint8_t read_register_byte(registers reg_to_read)
		{
			return cpu_read_register_byte(z80, reg_to_read);
		}

		uint16_t read_register_word(registers reg_to_read)
		{
			return cpu_read_register_word(z80, reg_to_read);
		}

		uint8_t write_register_byte(registers reg_to_write, uint8_t value)
		{
			return cpu_write_register_byte(z80, reg_to_write, value);
		}

		uint16_t write_register_word(registers reg_to_write, uint16_t value)
		{
			return cpu_write_register_word(z80, reg_to_write, value);
		}

		uint8_t read_byte(uint16_t address)
		{
			return cpu_read_byte(z80, address);
		}

		void write_byte(uint16_t address, uint8_t value)
		{
			cpu_write_byte(z80, address, value);
		}

		uint16_t read_word(uint16_t address)
		{
			return cpu_read_word(z80, address);
		}

		void write_word(uint16_t address, uint16_t value)
		{
			cpu_write_word(z80, address, value);
		}

		void set_interrupt()
		{
			z80->interrupt = 1;
		}

		void reset_interrupt()
		{
			z80->interrupt = 0;
		}

		int execute(int cycles)
		{
			return cpu_execute(z80, cycles);
		}

		~CPU()
		{
			cpu_free(z80);
		}
	};
}
#endif /* INCLUDE_Z80E_Z80E_H_ */

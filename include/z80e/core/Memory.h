#ifndef INCLUDE_Z80E_CORE_MEMORY_H_
#define INCLUDE_Z80E_CORE_MEMORY_H_

#include <cstdint>

namespace Z80e
{
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
}

#endif /* INCLUDE_Z80E_MEMORY_H_ */

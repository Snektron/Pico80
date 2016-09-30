#ifndef INCLUDE_EMU_MEMORY_MEMORY_H_
#define INCLUDE_EMU_MEMORY_MEMORY_H_

#include <cstdint>
#include "emu/memory/MemoryBank.h"
#include "emu/memory/PageRegistery.h"
#include "z80e/z80e.h"

#define BANK_0 0
#define BANK_A 1
#define BANK_B 2
#define BANK_C 3

class Memory : public Z80e::Memory
{
private:
	PageRegistery *registery;
	MemoryBank* banks[4];

public:
	Memory();
	uint8_t read(uint16_t address);
	void write(uint16_t address, uint8_t value);
	MemoryBank* get_bank(int bank);
	PageRegistery* get_registery();
	~Memory();
};

#endif /* INCLUDE_EMU_MEMORY_MEMORY_H_ */

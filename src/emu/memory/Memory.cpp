#include <cstdint>
#include "emu/memory/Memory.h"
#include "emu/memory/MemoryBank.h"
#include "emu/memory/PageRegistery.h"
#include "core/Logger.h"
#include "z80e/z80e.h"

#define TAG "Memory"

Memory::Memory()
{
	Logger::info(TAG, "Initializing memory");

	registery = new PageRegistery();
	banks[BANK_0] = new MemoryBank(registery);
	banks[BANK_A] = new MemoryBank(registery);
	banks[BANK_B] = new MemoryBank(registery);
	banks[BANK_C] = new MemoryBank(registery);
}

uint8_t Memory::read(uint16_t address)
{
	return banks[address / MEM_PAGE_SIZE]->read(address % MEM_PAGE_SIZE);
}

void Memory::write(uint16_t address, uint8_t value)
{
	 banks[address / MEM_PAGE_SIZE]->write(address % MEM_PAGE_SIZE, value);
}

MemoryBank* Memory::get_bank(int bank)
{
	return banks[bank & 0x3];
}

PageRegistery* Memory::get_registery()
{
	return registery;
}

Memory::~Memory()
{
	Logger::info(TAG, "Destroying memory");

	delete registery;
	delete banks[BANK_0];
	delete banks[BANK_A];
	delete banks[BANK_B];
	delete banks[BANK_C];
}

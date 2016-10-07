#include <cstdint>
#include "emu/memory/Memory.h"
#include "emu/memory/PageManager.h"
#include "emu/memory/MemoryBank.h"
#include "emu/memory/Page.h"
#include "emu/device/StorageController.h"
#include "core/Logger.h"
#include "z80e/z80e.h"

#define TAG "Memory"

Memory::Memory(StorageController *store_ctrl)
{
	Logger::info(TAG, "Initializing memory");

	registery = new PageRegistery(store_ctrl);
	bank[BANK_0] = new MemoryBank(registery);
	bank[BANK_A] = new MemoryBank(registery);
	bank[BANK_B] = new MemoryBank(registery);
	bank[BANK_C] = new MemoryBank(registery);
}

uint8_t Memory::read(uint16_t address)
{
	return bank[address / PAGE_SIZE]->read(address % PAGE_SIZE);
}

void Memory::write(uint16_t address, uint8_t value)
{
	bank[address / PAGE_SIZE]->write(address % PAGE_SIZE, value);
}

MemoryBank* Memory::get_bank(int bank_index)
{
	return bank[bank_index & 0x3];
}

PageRegistery* Memory::get_registery()
{
	return registery;
}

Memory::~Memory()
{
	Logger::info(TAG, "Destroying memory");

	delete registery;
	delete bank[BANK_0];
	delete bank[BANK_A];
	delete bank[BANK_B];
	delete bank[BANK_C];
}

#include <cstdint>
#include <memory>
#include "emu/pico80/memory/Memory.h"
#include "emu/pico80/memory/PageManager.h"
#include "emu/pico80/memory/MemoryBank.h"
#include "emu/pico80/memory/Page.h"
#include "emu/pico80/device/StorageController.h"
#include "core/Logger.h"
#include "z80e/z80e.h"

#define TAG "Memory"

Memory::Memory(std::shared_ptr<StorageController> store_ctrl)
{
	Logger::info(TAG, "Initializing memory");

	registery = std::make_shared<PageRegistery>(store_ctrl);
	bank[BANK_0] = std::make_shared<MemoryBank>(registery);
	bank[BANK_A] = std::make_shared<MemoryBank>(registery);
	bank[BANK_B] = std::make_shared<MemoryBank>(registery);
	bank[BANK_C] = std::make_shared<MemoryBank>(registery);
}

uint8_t Memory::read(uint16_t address)
{
	return bank[address / PAGE_SIZE]->read(address % PAGE_SIZE);
}

void Memory::write(uint16_t address, uint8_t value)
{
	bank[address / PAGE_SIZE]->write(address % PAGE_SIZE, value);
}

std::shared_ptr<MemoryBank> Memory::get_bank(int bank_index)
{
	return bank[bank_index & 0x3];
}

std::shared_ptr<PageRegistery> Memory::get_registery()
{
	return registery;
}

Memory::~Memory()
{
	Logger::info(TAG, "Destroying memory");
}

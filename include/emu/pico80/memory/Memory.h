#ifndef INCLUDE_EMU_MEMORY_MEMORY_H_
#define INCLUDE_EMU_MEMORY_MEMORY_H_

#include <cstdint>
#include <memory>
#include "emu/pico80/memory/MemoryBank.h"
#include "emu/pico80/memory/PageManager.h"
#include "emu/pico80/device/StorageController.h"
#include "z80e/z80e.h"

#define BANK_0 0
#define BANK_A 1
#define BANK_B 2
#define BANK_C 3

class Memory : public Z80e::Memory
{
private:
	std::shared_ptr<PageRegistery> registery;
	std::shared_ptr<MemoryBank> bank[4];

public:
	Memory(std::shared_ptr<StorageController> store_ctrl);
	uint8_t read(uint16_t address);
	void write(uint16_t address, uint8_t value);
	std::shared_ptr<MemoryBank> get_bank(int bank);
	std::shared_ptr<PageRegistery> get_registery();
	~Memory();
};

#endif /* INCLUDE_EMU_MEMORY_MEMORY_H_ */

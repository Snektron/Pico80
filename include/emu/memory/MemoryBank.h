#ifndef INCLUDE_EMU_MEMORY_MEMORYBANK_H_
#define INCLUDE_EMU_MEMORY_MEMORYBANK_H_

#include <cstdint>
#include "emu/memory/PageRegistery.h"
#include "emu/memory/MemoryPage.h"
#include "z80e/z80e.h"

class MemoryBank : public Z80e::BasicIODevice
{
private:
	PageRegistery *registery;
	MemoryPage *page;

public:
	MemoryBank(PageRegistery *registery):
		registery(registery),
		page(nullptr)
	{}

	void write(uint8_t value)
	{
		page = registery->get_page(value);
		Z80e::BasicIODevice::write(value);
	}

	void write(uint16_t address, uint8_t value)
	{
		if (page)
			page->write(address, value);
	}

	uint8_t read(uint16_t address)
	{
		if (page)
			return page->read(address);
		return 0;
	}
};

#endif /* INCLUDE_EMU_MEMORY_MEMORYBANK_H_ */

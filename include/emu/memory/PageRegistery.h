#ifndef INCLUDE_EMU_MEMORY_PAGEREGISTERY_H_
#define INCLUDE_EMU_MEMORY_PAGEREGISTERY_H_

#include <cstdint>
#include "emu/memory/MemoryPage.h"

#define NUM_RAM_PAGES 4

class PageRegistery
{
private:
	std::vector<MemoryPage*> rom;
	MemoryPage* ram[NUM_RAM_PAGES];

public:
	PageRegistery();
	MemoryPage* get_page(uint8_t page);
	~PageRegistery();
};

#endif /* INCLUDE_EMU_MEMORY_PAGEREGISTERY_H_ */

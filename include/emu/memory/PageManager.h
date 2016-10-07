#ifndef INCLUDE_EMU_MEMORY_PAGEMANAGER_H_
#define INCLUDE_EMU_MEMORY_PAGEMANAGER_H_

#include <cstdint>
#include "emu/memory/Page.h"
#include "emu/device/StorageController.h"
#include "z80e/z80e.h"

#define NUM_RAM_PAGES 2
#define RAM_PAGE(page) (0x80 + (page))

class PageRegistery
{
private:
	Page* pages[0x100];
	int rom_pages;

	int read_rom(StorageController *store_ctrl);
	void save_rom();

public:
	PageRegistery(StorageController *store_ctrl);
	Page* get_page(uint8_t page);
	~PageRegistery();
};

#endif /* INCLUDE_EMU_MEMORY_PAGEMANAGER_H_ */

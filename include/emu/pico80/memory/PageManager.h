#ifndef INCLUDE_EMU_MEMORY_PAGEMANAGER_H_
#define INCLUDE_EMU_MEMORY_PAGEMANAGER_H_

#include <cstdint>
#include <memory>
#include "emu/pico80/memory/Page.h"
#include "emu/pico80/device/StorageController.h"
#include "z80e/z80e.h"

#define NUM_RAM_PAGES 2
#define RAM_PAGE(page) (0x80 + (page))

class PageRegistery
{
private:
	std::shared_ptr<Page> pages[0x100];
	int rom_pages;

	int load_rom(std::shared_ptr<StorageController> store_ctrl);
	void save_rom();

public:
	PageRegistery(std::shared_ptr<StorageController> store_ctrl);
	std::shared_ptr<Page> get_page(uint8_t page);
	~PageRegistery();
};

#endif /* INCLUDE_EMU_MEMORY_PAGEMANAGER_H_ */

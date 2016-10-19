#include <cstdint>
#include <fstream>
#include <exception>
#include <ostream>
#include <iomanip>
#include "emu/memory/PageManager.h"
#include "emu/device/StorageController.h"
#include "core/Logger.h"

#define TAG "PageManager"
#define ROM_IMAGE "rom.bin"

std::ostream& hex(std::ostream& os, int value)
{
	os << "0x";
	os << std::setfill('0');
	os << std::setw(2);
	os << std::uppercase;
	os << std::hex;
	os << value;
	os << std::dec;
	os << std::nouppercase;
	return os;
}

std::ostream& hexrange(std::ostream& os, int low, int high)
{
	return hex(hex(os, low) << " - ", high);
}

PageRegistery::PageRegistery(StorageController *store_ctrl):
	pages()
{
	Logger::info(TAG, "Initializing page manager");

	rom_pages = read_rom(store_ctrl);
	Logger::info(TAG) << "Loaded " << rom_pages << " rom page(s)" << Logger::endl;

	for (int i = 0; i < NUM_RAM_PAGES; i++)
		pages[RAM_PAGE(i)] = new MemoryPage();

	Logger::info(TAG, "Memory mapping:");
	hexrange(Logger::info(TAG) << "Page ", 0, rom_pages - 1) << ": rom" << Logger::endl;
	hexrange(Logger::info(TAG) << "Page ", RAM_PAGE(0), RAM_PAGE(NUM_RAM_PAGES - 1)) << ": memory" << Logger::endl;
}

Page* PageRegistery::get_page(uint8_t page)
{
	return pages[page];
}

PageRegistery::~PageRegistery()
{
	Logger::info(TAG, "Destroying page manager");

	save_rom();

	for (int i = 0; i < 0x100; i++)
		if (pages[i])
			delete pages[i];
}

int PageRegistery::read_rom(StorageController *store_ctrl)
{
	std::ifstream rom_image(ROM_IMAGE, std::ios::binary);

	if (!rom_image.is_open())
	{
		Logger::error(TAG, "Failed to open kernel image");
		throw new std::runtime_error("Error initializing page manager");
	}

	int index = 0;
	while (!rom_image.eof())
	{
		StoragePage *page = new StoragePage(store_ctrl);
		rom_image.read((char*) page->raw_data(), PAGE_SIZE);
		pages[index++] = page;
		if (index >= 128)
		{
			Logger::error(TAG, "Too many storage pages");
			throw new std::runtime_error("Error initializing page manager");
		}
	}
	rom_image.close();

	return index;
}

void PageRegistery::save_rom()
{
	Logger::info(TAG, "Saving rom");
	std::ofstream rom_image(ROM_IMAGE, std::ios::binary);

	if (!rom_image)
	{
		Logger::error(TAG, "Failed opening rom image");
		return;
	}

	for (int i = 0; i < rom_pages; i++)
	{
		Page *page = pages[i];
		rom_image.write((char*) page->raw_data(), PAGE_SIZE);
	}
	rom_image.close();
}

#include "emu/memory/PageManager.h"
#include <cstdint>
#include <fstream>
#include <exception>
#include <ostream>
#include <iomanip>
#include <memory>
#include "emu/device/StorageController.h"
#include "core/Logger.h"
#include "Settings.h"

#define TAG "PageManager"

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

PageRegistery::PageRegistery(std::shared_ptr<StorageController> store_ctrl):
	pages()
{
	Logger::info(TAG, "Initializing page manager");

	rom_pages = load_rom(store_ctrl);
	Logger::info(TAG) << "Loaded " << rom_pages << " rom page(s)" << Logger::endl;

	for (int i = 0; i < NUM_RAM_PAGES; i++)
		pages[RAM_PAGE(i)] = std::make_shared<MemoryPage>();

	Logger::info(TAG, "Memory mapping:");
	hexrange(Logger::info(TAG) << "Page ", 0, rom_pages - 1) << ": rom" << Logger::endl;
	hexrange(Logger::info(TAG) << "Page ", RAM_PAGE(0), RAM_PAGE(NUM_RAM_PAGES - 1)) << ": memory" << Logger::endl;
}

std::shared_ptr<Page> PageRegistery::get_page(uint8_t page)
{
	return pages[page];
}

PageRegistery::~PageRegistery()
{
	if (Settings::save_rom())
		save_rom();
}

int PageRegistery::load_rom(std::shared_ptr<StorageController> store_ctrl)
{
	std::string rom_location = Settings::get_rom();
	std::ifstream rom_image(rom_location, std::ios::binary);

	Logger::info(TAG) << "Loading rom image " << rom_location << Logger::endl;
	if (!rom_image.is_open())
	{
		Logger::error(TAG, "Failed to open rom image");
		throw new std::runtime_error("Error initializing page manager");
	}

	rom_image.seekg (0, rom_image.end);
	int length = rom_image.tellg();
	rom_image.seekg (0, rom_image.beg);
	int n = (length + 16383)/PAGE_SIZE;

	if (n > 128)
	{
		Logger::error(TAG) << "Too many rom pages (" << n << ")" << Logger::endl;
		throw new std::runtime_error("Error initializing page manager");
	}

	int i = 0;
	for (; i < n; i++)
	{
		auto page = std::make_shared<StoragePage>(store_ctrl);
		rom_image.read((char*) page->raw_data(), PAGE_SIZE);
		pages[i] = page;
	}

	rom_image.close();

	return n;
}

void PageRegistery::save_rom()
{
	Logger::info(TAG, "Saving rom");
	std::ofstream rom_image(Settings::get_rom(), std::ios::binary);

	if (!rom_image)
	{
		Logger::error(TAG, "Failed opening rom image");
		return;
	}

	for (int i = 0; i < rom_pages - 1; i++)
	{
		auto page = pages[i];
		rom_image.write((char*) page->raw_data(), PAGE_SIZE);
	}
	rom_image.close();
}

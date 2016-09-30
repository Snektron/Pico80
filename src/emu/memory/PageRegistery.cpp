#include <cstdint>
#include <fstream>
#include <exception>
#include <algorithm>
#include <vector>
#include "emu/memory/PageRegistery.h"
#include "core/Logger.h"

#define TAG "PageRegistery"
#define KERNEL_IMAGE "kernel.bin"

PageRegistery::PageRegistery()
{
	Logger::info(TAG, "Initializing memory");
	std::ifstream rom_image(KERNEL_IMAGE, std::ios::binary);

	if (!rom_image.is_open())
	{
		Logger::error(TAG, "Failed to open rom image");
		throw new std::runtime_error("Error initializing page registery");
	}

	while (!rom_image.eof())
	{
		MemoryPage *page = new MemoryPage(false);
		rom_image.read((char*) page->raw_data(), MEM_PAGE_SIZE);
		rom.push_back(page);
	}

	if (rom.size() >= 128)
	{
		Logger::error(TAG, "Too many rom pages");
		throw new std::runtime_error("Error initializing page registery");
	}

	Logger::info(TAG) << "Loaded " << rom.size() << " rom page(s)" << Logger::endl;

	rom_image.close();

	for (int i = 0; i < NUM_RAM_PAGES; i++)
		ram[i] = new MemoryPage(true);
}

MemoryPage* PageRegistery::get_page(uint8_t page)
{
	if (page & 0x80) // bit 1 indicated ram page
	{
		if (page - 0x80 < NUM_RAM_PAGES)
			return ram[page - 0x80];
	}
	else
	{
		if (page < rom.size())
			return rom[page];
	}
	return nullptr;
}

PageRegistery::~PageRegistery()
{
	Logger::info(TAG, "Destroying page registery");

	for (int i = 0; i < NUM_RAM_PAGES; i++)
		delete ram[i];
	for (MemoryPage *page : rom)
		delete page;
}

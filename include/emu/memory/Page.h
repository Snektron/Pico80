#ifndef INCLUDE_EMU_MEMORY_PAGE_H_
#define INCLUDE_EMU_MEMORY_PAGE_H_

#include <algorithm>
#include "emu/device/StorageController.h"

#define PAGE_SIZE 16384

class Page
{
protected:
	uint8_t data[PAGE_SIZE];

public:
	Page()
	{
		std::fill_n(data, PAGE_SIZE, 0xFF);
	}

	virtual uint8_t read(uint16_t address)
	{
		return data[address % PAGE_SIZE];
	}

	virtual void write(uint16_t address, uint8_t value) = 0;

	virtual uint8_t* raw_data()
	{
		return data;
	}

	virtual ~Page() = default;
};

class MemoryPage : public Page
{
public:
	void write(uint16_t address, uint8_t value)
	{
		data[address % PAGE_SIZE] = value;
	}
};

class StoragePage : public Page
{
private:
	StorageController *store_ctrl;

public:
	StoragePage(StorageController *store_ctrl):
		store_ctrl(store_ctrl)
	{}

	void write(uint16_t address, uint8_t value)
	{
		if (!store_ctrl->is_locked())
			data[address % PAGE_SIZE] = value;
	}
};

#endif /* INCLUDE_EMU_MEMORY_PAGE_H_ */

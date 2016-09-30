#ifndef INCLUDE_EMU_MEMORY_MEMORYPAGE_H_
#define INCLUDE_EMU_MEMORY_MEMORYPAGE_H_

#include <algorithm>

#define MEM_PAGE_SIZE 16384

class MemoryPage
{
private:
	bool writable;
	uint8_t data[MEM_PAGE_SIZE];

public:
	MemoryPage(bool writable):
		writable(writable)
	{
		std::fill(data, data + MEM_PAGE_SIZE, 0xFF);
	}

	uint8_t read(uint16_t address)
	{
		return data[address % MEM_PAGE_SIZE];
	}

	void write(uint16_t address, uint8_t value)
	{
		if (writable)
			data[address % MEM_PAGE_SIZE] = value;
	}

	uint8_t* raw_data()
	{
		return data;
	}
};

#endif /* INCLUDE_EMU_MEMORY_MEMORYPAGE_H_ */

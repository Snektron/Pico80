#ifndef INCLUDE_EMU_DEVICE_LOG_H_
#define INCLUDE_EMU_DEVICE_LOG_H_

#include <cstdint>
#include <sstream>
#include "core/Logger.h"
#include "z80e/z80e.h"

class Log : public Z80e::IODevice
{
private:
	std::stringstream buffer;

public:
	void write(uint8_t value)
	{
		if (value)
			buffer.put((char) value);
		else
		{
			Logger::info("Z80", buffer.str());
			buffer.str("");
		}
	}

	uint8_t read()
	{
		return 0;
	}
};

#endif /* INCLUDE_EMU_DEVICE_LOG_H_ */

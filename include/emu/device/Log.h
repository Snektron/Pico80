#ifndef INCLUDE_EMU_DEVICE_LOG_H_
#define INCLUDE_EMU_DEVICE_LOG_H_

#include <cstdint>
#include <string>
#include "core/Logger.h"
#include "z80e/z80e.h"

class Log : public Z80e::IODevice
{
private:
	std::string buffer;

public:
	void write(uint8_t value)
	{
		if (value)
			buffer.append(std::string(1, (char) value));
		else
		{
			Logger::info("Z80", buffer);
			buffer = "";
		}
	}

	uint8_t read()
	{
		return 0;
	}
};

#endif /* INCLUDE_EMU_DEVICE_LOG_H_ */

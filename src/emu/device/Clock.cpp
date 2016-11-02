#include "emu/device/Clock.h"
#include <cstdint>
#include "core/Time.h"

ClockReg::ClockReg(int byte):
	byte(byte)
{}

uint8_t ClockReg::read()
{
	return (uint8_t) (Time::secondsSince1997() >> byte * 8 & 0xFF);
}

void ClockReg::write(uint8_t value)
{}

#include "emu/pico80/device/Screen.h"
#include <cstring>
#include "core/Logger.h"
#include "z80e/z80e.h"

#define TAG "Screen"

void Vram::clear(uint8_t color)
{
	std::memset(data, color & 0xF, SCREEN_WIDTH * SCREEN_HEIGHT);
}

void Vram::setPixel(uint8_t x, uint8_t y, uint8_t color)
{
	data[SCREEN_INDEX(x, y)] = color & 0xF;
}

uint8_t Vram::getPixel(uint8_t x, uint8_t y)
{
	return data[SCREEN_INDEX(x, y)] & 0xF;
}

uint8_t* Vram::rawData()
{
	return data;
}

Screen::Screen():
	arg0(new Z80e::BasicIODevice()),
	arg1(new Z80e::BasicIODevice()),
	arg2(new Z80e::BasicIODevice()),
	vram(new Vram())
{
	vram->clear(0);
}

Screen::~Screen()
{
	delete vram;
}

void Screen::write(uint8_t value)
{
	switch(value)
	{
	case SC_INVALIDATE:
		emit invalidate(vram);
		break;
	case SC_CLEAR:
		vram->clear(arg0->read());
		break;
	case SC_SET_PIXEL:
		vram->setPixel(arg1->read(), arg2->read(), arg0->read());
		break;
	case SC_GET_PIXEL:
		arg0->write(vram->getPixel(arg1->read(), arg2->read()));
		break;
	default:
		Logger::warn(TAG) << "Unknown command written: " << value << Logger::endl;
		break;
	}
}

uint8_t Screen::read()
{
	return 0;
}

std::shared_ptr<Z80e::BasicIODevice> Screen::get_arg0()
{
	return arg0;
}

std::shared_ptr<Z80e::BasicIODevice> Screen::get_arg1()
{
	return arg1;
}

std::shared_ptr<Z80e::BasicIODevice> Screen::get_arg2()
{
	return arg2;
}

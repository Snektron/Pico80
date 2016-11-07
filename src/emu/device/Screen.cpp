#include "emu/device/Screen.h"
#include <cstdint>
#include <cstring>
#include <memory>
#include "core/Logger.h"
#include "emu/Display.h"
#include "z80e/z80e.h"

#define TAG "Screen"

Screen::Screen():
	arg0(new Z80e::BasicIODevice()),
	arg1(new Z80e::BasicIODevice()),
	arg2(new Z80e::BasicIODevice()),
	valid(false)
{
	clear(0);
}

void Screen::write(uint8_t value)
{
	switch(value)
	{
	case SC_INVALIDATE:
		invalidate();
		break;
	case SC_CLEAR:
		clear(arg0->read());
		break;
	case SC_SET_PIXEL:
		set_pixel(arg1->read(), arg2->read(), arg0->read());
		break;
	case SC_GET_PIXEL:
		arg0->write(get_pixel(arg1->read(), arg2->read()));
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

void Screen::clear(uint8_t color)
{
	std::memset(vram, color, DISPLAY_WIDTH * DISPLAY_HEIGHT);
}

void Screen::set_pixel(uint8_t x, uint8_t y, uint8_t color)
{
	vram[DISPLAY_INDEX(x, y)] = color;
}

uint8_t Screen::get_pixel(uint8_t x, uint8_t y)
{
	return vram[DISPLAY_INDEX(x, y)];
}

void Screen::invalidate()
{
	valid = false;
}

void Screen::validate()
{
	valid = true;
}

bool Screen::isValid()
{
	return valid;
}

uint8_t* Screen::getVram()
{
	return vram;
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

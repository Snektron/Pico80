#include "emu/device/Mouse.h"
#include <cstdint>
#include <memory>
#include "core/Logger.h"
#include "z80e/z80e.h"
#include "emu/Platform.h"

int clamp(int x, int a, int b)
{
	return x < a ? a : x > b ? b : x;
}

uint8_t MouseX::read()
{
	return 0;
}

uint8_t MouseY::read()
{
	return 0;
}

uint8_t MouseState::read()
{
	return 0;
}

Mouse::Mouse():
	x(),
	y(),
	state()
{}

std::shared_ptr<MouseX> Mouse::get_mouse_x()
{
	return x;
}

std::shared_ptr<MouseY> Mouse::get_mouse_y()
{
	return y;
}

std::shared_ptr<MouseState> Mouse::get_mouse_state()
{
	return state;
}

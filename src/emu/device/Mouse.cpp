#include "emu/device/Mouse.h"
#include <cstdint>
#include <memory>
#include "core/Logger.h"
#include "core/Input.h"
#include "z80e/z80e.h"

int clamp(int x, int a, int b)
{
	return x < a ? a : x > b ? b : x;
}

uint8_t MouseX::read()
{
//	Display::rect_t dst;
//	Display::get_display_rect(dst);
//	int x = Input::Mouse::X();
//	return (uint8_t) clamp((x - dst.x) * DISPLAY_WIDTH / dst.w, 0, DISPLAY_WIDTH);
	return 0;
}

uint8_t MouseY::read()
{
//	Display::rect_t dst;
//	Display::get_display_rect(dst);
//	int y = Input::Mouse::Y();
//	return (uint8_t) clamp((y - dst.y) * DISPLAY_HEIGHT / dst.h, 0, DISPLAY_HEIGHT);
	return 0;
}

uint8_t MouseState::read()
{
	return (uint8_t) Input::Mouse::state();
}

void MouseState::write(uint8_t value)
{}

Mouse::Mouse():
	x(new MouseX()),
	y(new MouseY()),
	state(new MouseState())
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

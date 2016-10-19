#include <cstdint>
#include <SDL2/SDL.h>
#include "emu/device/Mouse.h"
#include "core/Logger.h"
#include "core/Input.h"
#include "core/Display.h"
#include "z80e/z80e.h"

MouseDevice::MouseDevice(Screen *screen):
	screen(screen)
{}

void MouseDevice::write(uint8_t value)
{}

int clamp(int x, int a, int b)
{
	return x < a ? a : x > b ? b : x;
}

uint8_t MouseX::read()
{
	SDL_Rect dst;
	Display::get_display_rect(dst);
	int x = Input::Mouse::X();
	return (uint8_t) clamp((x - dst.x) * DISPLAY_WIDTH / dst.w, 0, DISPLAY_WIDTH);
}

uint8_t MouseY::read()
{
	SDL_Rect dst;
	Display::get_display_rect(dst);
	int y = Input::Mouse::Y();
	return (uint8_t) clamp((y - dst.y) * DISPLAY_HEIGHT / dst.h, 0, DISPLAY_HEIGHT);
}

uint8_t MouseState::read()
{
	return (uint8_t) Input::Mouse::State();
}

void MouseState::write(uint8_t value)
{}

Mouse::Mouse(Screen *screen):
		x(screen),
		y(screen)
{}

MouseX* Mouse::get_mouse_x()
{
	return &x;
}

MouseY* Mouse::get_mouse_y()
{
	return &y;
}

MouseState* Mouse::get_mouse_state()
{
	return &state;
}

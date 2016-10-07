#include <cstdint>
#include <SDL2/SDL.h>
#include "emu/device/Mouse.h"
#include "emu/device/Screen.h"
#include "core/Logger.h"
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
	SDL_Rect scrn;
	screen->get_screen_rect(scrn);
	int x;
	SDL_GetMouseState(&x, NULL);
	return (uint8_t) clamp((x - scrn.x) * SCREEN_WIDTH / scrn.w, 0, SCREEN_WIDTH);
}

uint8_t MouseY::read()
{
	SDL_Rect scrn;
	screen->get_screen_rect(scrn);
	int y;
	SDL_GetMouseState(&y, NULL);
	return (uint8_t) clamp((y - scrn.y) * SCREEN_HEIGHT / scrn.h, 0, SCREEN_HEIGHT);
}

uint8_t MouseState::read()
{
	uint8_t state = 0;
	uint32_t mouse = SDL_GetMouseState(NULL, NULL);

	state |= ((mouse >> (SDL_BUTTON_LEFT - 1)) & 1) << MOUSE_BTN_LEFT;
	state |= ((mouse >> (SDL_BUTTON_RIGHT - 1)) & 1) << MOUSE_BTN_RIGHT;
	state |= ((mouse >> (SDL_BUTTON_MIDDLE - 1)) & 1) << MOUSE_BTN_MIDDLE;

	return state;
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

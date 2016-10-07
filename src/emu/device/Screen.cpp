#include <cstdint>
#include <cstring>
#include <algorithm>
#include "emu/device/Screen.h"
#include "core/Graphics.h"
#include "core/Logger.h"
#include "z80e/z80e.h"

#define TAG "Screen"
#define SCREEN_INDEX(x, y) (SCREEN_WIDTH * (y & 0x7F) + (x & 0x7F))

#define COLOR(col) {((col) >> 16) & 0xFF, ((col) >> 8) & 0xFF, ((col) & 0xFF), 0xFF}

const SDL_Color palette[16] =
{
	COLOR(0x000000), // Black [Black]
	COLOR(0x2196F3), // Blue [Blue 500]
	COLOR(0x4CAF50), // Green [Green 500]
	COLOR(0x009688), // Teal [Teal 500]
	COLOR(0x795548), // Brown [Brown 500]
	COLOR(0x9C27B0), // Purple [Purple 500]
	COLOR(0xFF9800), // Orange [Orange 500]
	COLOR(0xBDBDBD), // Light gray [Gray 400]
	COLOR(0x616161), // Dark gray [Grey 700]
	COLOR(0x03A9F4), // Light Blue [Light Blue 500]
	COLOR(0x8BC34A), // Light Green [Light Green 500]
	COLOR(0x00BCD4), // Cyan [Cyan 500]
	COLOR(0xF44336), // Red [Red 500]
	COLOR(0xE91E63), // Pink [Pink 500]
	COLOR(0xFFEE58), // Yellow [Yellow 400]
	COLOR(0xFFFFFF), // White [Grey]
};

Screen::Screen()
{
	Logger::info(TAG, "Initializing screen");

	display = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);

	if (display == NULL)
	{
		Logger::info(TAG) << "Failed to create screen display: " << SDL_GetError() << Logger::endl;
		throw std::runtime_error("Failed to initialize screen");
	}

	clear(1);
	sync();
}

Screen::~Screen()
{
	Logger::info(TAG, "Destroying screen");
	SDL_FreeSurface(display);
}

void Screen::get_screen_rect(SDL_Rect& rect)
{
	int w = Graphics::get_width(), h = Graphics::get_height();
	int pix = std::min(w / SCREEN_WIDTH, h / SCREEN_HEIGHT);
	int sw = pix * SCREEN_WIDTH, sh = pix * SCREEN_HEIGHT;
	rect.x = (w - sw) / 2;
	rect.y = (h - sw) / 2;
	rect.w = sw;
	rect.h = sh;
}

void Screen::render()
{
	SDL_Rect dst;
	get_screen_rect(dst);

	SDL_BlitScaled(display, NULL, Graphics::get_surface(), &dst);
}

void Screen::write(uint8_t value)
{
	switch(value)
	{
	case SC_SYNC:
		Screen::sync();
		break;
	case SC_CLEAR:
		clear(arg0.read());
		break;
	case SC_SET_PIXEL:
		set_pixel(arg1.read(), arg2.read(), arg0.read());
		break;
	case SC_GET_PIXEL:
		arg0.write(get_pixel(arg1.read(), arg2.read()));
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

void Screen::sync()
{
	uint32_t *pixels = (uint32_t*) display->pixels;
	for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++)
		pixels[i] = palcol(vram[i]);
}

void Screen::clear(uint8_t color)
{
	std::memset(vram, color, SCREEN_WIDTH * SCREEN_HEIGHT);
}

void Screen::set_pixel(uint8_t x, uint8_t y, uint8_t color)
{
	vram[SCREEN_INDEX(x, y)] = color;
}

uint8_t Screen::get_pixel(uint8_t x, uint8_t y)
{
	return vram[SCREEN_INDEX(x, y)];
}

uint32_t Screen::palcol(uint8_t index)
{
	SDL_Color color = palette[index & 0xF];
	return SDL_MapRGB(display->format, color.r, color.g, color.b);
}

Z80e::BasicIODevice* Screen::get_arg0()
{
	return &arg0;
}

Z80e::BasicIODevice* Screen::get_arg1()
{
	return &arg1;
}

Z80e::BasicIODevice* Screen::get_arg2()
{
	return &arg2;
}

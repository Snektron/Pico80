#include "core/Display.h"
#include <algorithm>
#include <mutex>
#include <SDL2/SDL.h>
#include "core/Graphics.h"
#include "core/Logger.h"

#define TAG "Display"
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

namespace Display
{
	namespace
	{
		SDL_Surface *display;
		std::mutex mutex;
	}

	void init()
	{
		std::lock_guard<std::mutex> lock(mutex);
		Logger::info(TAG, "Initializing display");

		display = SDL_CreateRGBSurface(0, DISPLAY_WIDTH, DISPLAY_HEIGHT, 32, 0, 0, 0, 0);

		if (display == NULL)
		{
			Logger::info(TAG) << "Failed to create display: " << SDL_GetError() << Logger::endl;
			throw std::runtime_error("Failed to initialize display");
		}
	}

	void render()
	{
		std::lock_guard<std::mutex> lock(mutex);
		SDL_Rect dst;
		get_display_rect(dst);
		SDL_BlitScaled(display, NULL, Graphics::get_surface(), &dst);
	}

	void destroy()
	{
		std::lock_guard<std::mutex> lock(mutex);
		Logger::info(TAG, "Destroying display");
		if (!display)
			return;
		SDL_FreeSurface(display);
	}

	void write(uint8_t *data)
	{
		std::lock_guard<std::mutex> lock(mutex);
		if (!display)
			return;
		uint32_t *pixels = (uint32_t*) display->pixels;
		for (int i = 0; i < DISPLAY_WIDTH * DISPLAY_HEIGHT; i++)
		{
			SDL_Color color = palette[data[i] & 0xF];
			pixels[i] = SDL_MapRGB(display->format, color.r, color.g, color.b);
		}
	}

	void get_display_rect(SDL_Rect& rect)
	{
		int w = Graphics::get_width(), h = Graphics::get_height();
		int pix = std::min(w / DISPLAY_WIDTH, h / DISPLAY_HEIGHT);
		int sw = pix * DISPLAY_WIDTH, sh = pix * DISPLAY_HEIGHT;
		rect.x = (w - sw) / 2;
		rect.y = (h - sw) / 2;
		rect.w = sw;
		rect.h = sh;
	}
}

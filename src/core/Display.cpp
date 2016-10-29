#include "core/Display.h"
#include <algorithm>
#include <mutex>
#include <memory>
#include "core/Graphics.h"
#include "core/Logger.h"

#define TAG "Display"
#define SCREEN_INDEX(x, y) (SCREEN_WIDTH * (y & 0x7F) + (x & 0x7F))
//#define COLOR(col) {((col) >> 16) & 0xFF, ((col) >> 8) & 0xFF, ((col) & 0xFF), 0xFF}
#define COLOR(r, g, b) {r, g, b}

const SDL_Color palette[16] =
{
	{ 20,  12,  28}, // black
	{ 68,  36,  52}, // plum
	{ 48,  52, 109}, // midnight
	{ 78,  74,  78}, // iron
	{133,  76,  48}, // earth
	{ 52, 101,  36}, // moss
	{208,  70,  72}, // berry
	{117, 113,  97}, // olive
	{ 89, 125, 206}, // cornflower
	{210, 125,  44}, // ocher
	{133, 149, 161}, // slate
	{109, 170,  44}, // leaf
	{210, 170, 153}, // peach
	{109, 194, 202}, // sky
	{218, 212,  94}, // maize
	{222, 238, 214}  // peppermint
};

namespace Display
{
	namespace
	{
		std::unique_ptr<SDL_Surface> display;
		std::mutex mutex;
	}

	void init()
	{
		std::lock_guard<std::mutex> lock(mutex);

		Logger::info(TAG, "Initializing display");

		display = std::unique_ptr<SDL_Surface>(SDL_CreateRGBSurface(0, DISPLAY_WIDTH, DISPLAY_HEIGHT, 32, 0, 0, 0, 0));

		if (!display)
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
		Graphics::blit(display.get(), dst);
	}

	void destroy()
	{
		std::lock_guard<std::mutex> lock(mutex);

		Logger::info(TAG, "Destroying display");
		SDL_FreeSurface(display.release());
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

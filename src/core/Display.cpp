#include "core/Display.h"
#include <algorithm>
#include <memory>
#include <cstdint>
#include <Eigen/Core>
#include "glad/glad.h"
#include "core/Graphics.h"
#include "core/Logger.h"

#define TAG "Display"
#define SCREEN_INDEX(x, y) (SCREEN_WIDTH * (y & 0x7F) + (x & 0x7F))
#define COLOR(r, g, b) {r, g, b, 0xFF}

typedef union
{
	struct { uint8_t r, g, b, a; };
	uint32_t rgba;
} color_t;

const color_t palette[16] =
{
	COLOR( 20,  12,  28), // 0 black
	COLOR( 68,  36,  52), // 1 plum
	COLOR( 48,  52, 109), // 2 midnight
	COLOR( 78,  74,  78), // 3 iron
	COLOR(133,  76,  48), // 4 earth
	COLOR( 52, 101,  36), // 5 moss
	COLOR(208,  70,  72), // 6 berry
	COLOR(117, 113,  97), // 7 olive

	COLOR( 89, 125, 206), // 8 cornflower
	COLOR(210, 125,  44), // 9 ocher
	COLOR(133, 149, 161), // A slate
	COLOR(109, 170,  44), // B leaf
	COLOR(210, 170, 153), // C peach
	COLOR(109, 194, 202), // D sky
	COLOR(218, 212,  94), // E maize
	COLOR(222, 238, 214)  // F peppermint
};

namespace Display
{
	namespace
	{
		GLuint texture;
		color_t pixels[DISPLAY_WIDTH * DISPLAY_HEIGHT] = {0};
	}

	void init()
	{
		Logger::info(TAG, "Initializing display");

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, DISPLAY_WIDTH, DISPLAY_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	}

	void render()
	{
		rect_t dst;
		get_display_rect(dst);
	}

	void destroy()
	{
		Logger::info(TAG, "Destroying display");
		glDeleteTextures(1, &texture);
	}

	void write(uint8_t *data)
	{
		if (!texture)
			return;

		for (int i = 0; i < DISPLAY_WIDTH * DISPLAY_HEIGHT; i++)
			pixels[i] = palette[data[i] & 0xF];

		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	}

	void get_display_rect(rect_t& rect)
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

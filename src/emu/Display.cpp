#include "emu/Display.h"
#include <cstdint>
#include <nanovg.h>
#include "core/Graphics.h"
#include "core/Logger.h"
#define TAG "Display"

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

float vertices[] =
{
	0, 0,
	0, 1,
	1, 1,

	0, 0,
	1, 1,
	1, 0
};

Display::Display():
	renderWidth(0),
	renderHeight(0)
{
	Logger::info(TAG, "Initializing display");
	image = nvgCreateImageRGBA(Graphics::nvg(), DISPLAY_WIDTH, DISPLAY_HEIGHT, 0, (unsigned char*) pixels);
}

void Display::onRender()
{
	NVGcontext *vg = Graphics::nvg();
	NVGpaint paint = nvgImagePattern(vg, x, y, width, height, 0, image, 1);
	nvgBeginPath(vg);
	nvgRect(vg, x, y, width, height);
	nvgFillPaint(vg, paint);
	nvgFill(vg);
}

Display::~Display()
{
	nvgDeleteImage(Graphics::nvg(), image);
}

void Display::write(uint8_t *data)
{
	for (int i = 0; i < DISPLAY_WIDTH * DISPLAY_HEIGHT; i++)
		pixels[i] = palette[data[i] & 0xF];

	nvgUpdateImage(Graphics::nvg(), image, (unsigned char*) pixels);
}

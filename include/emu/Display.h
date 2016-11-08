#ifndef INCLUDE_CORE_DISPLAY_H_
#define INCLUDE_CORE_DISPLAY_H_

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 128
#define DISPLAY_INDEX(x, y) (DISPLAY_WIDTH * (y & 0x7F) + (x & 0x7F))

#include <cstdint>
#include "core/view/View.h"

#define COLOR(r, g, b) {r, g, b, 0xFF}

typedef union
{
	struct { uint8_t r, g, b, a; };
	uint32_t rgba;
} color_t;

class Display : public View
{
private:
	color_t pixels[DISPLAY_WIDTH * DISPLAY_HEIGHT];
	int image;
	int renderWidth, renderHeight;

public:
	Display();
	void onRender();
	void write(uint8_t *data);
	~Display();
};

#endif /* INCLUDE_CORE_DISPLAY_H_ */

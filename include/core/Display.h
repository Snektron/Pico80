#ifndef INCLUDE_CORE_DISPLAY_H_
#define INCLUDE_CORE_DISPLAY_H_

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 128
#define DISPLAY_INDEX(x, y) (DISPLAY_WIDTH * (y & 0x7F) + (x & 0x7F))

#include <cstdint>

namespace Display
{
	typedef struct {int x, y, w, h;} rect_t;
	void init();
	void render();
	void destroy();
	void write(uint8_t *data);
	void get_display_rect(rect_t& rect);
}

#endif /* INCLUDE_CORE_DISPLAY_H_ */

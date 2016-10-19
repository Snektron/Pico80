#ifndef INCLUDE_CORE_DISPLAY_H_
#define INCLUDE_CORE_DISPLAY_H_

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 128
#define DISPLAY_INDEX(x, y) (DISPLAY_WIDTH * (y & 0x7F) + (x & 0x7F))

#include <cstdint>
#include <SDL2/SDL.h>

namespace Display
{
	void init();
	void render();
	void destroy();
	void write(uint8_t *data);
	void get_display_rect(SDL_Rect& rect);
}

#endif /* INCLUDE_CORE_DISPLAY_H_ */

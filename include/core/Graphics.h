#ifndef INCLUDE_CORE_GRAPHICS_H_
#define INCLUDE_CORE_GRAPHICS_H_

#include <string>
#include <SDL2/SDL.h>

namespace Graphics
{
	void init(std::string name, int w, int h);
	void update();
	void destroy();
	void refresh_surface();
	void clear();
	int get_width();
	int get_height();
	SDL_Window* get_window();
	SDL_Surface* get_surface();
}

#endif /* INCLUDE_CORE_GRAPHICS_H_ */

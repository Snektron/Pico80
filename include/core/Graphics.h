#ifndef INCLUDE_CORE_GRAPHICS_H_
#define INCLUDE_CORE_GRAPHICS_H_

#include <string>
#include <SDL2/SDL.h>

namespace Graphics
{
	void init(std::string name, int w, int h);
	void destroy();
	void update();
	void refresh_surface();

	void clear();
	void blit(SDL_Surface *src, SDL_Rect& dstrect);

	int get_width();
	int get_height();
}

#endif /* INCLUDE_CORE_GRAPHICS_H_ */

#ifndef INCLUDE_CORE_GRAPHICS_H___
#define INCLUDE_CORE_GRAPHICS_H___

#include <string>

namespace Graphics
{
	void init(std::string name, int w, int h);
	void destroy();
	void update();

	int get_width();
	int get_height();
}

#endif /* INCLUDE_CORE_GRAPHICS_H___ */

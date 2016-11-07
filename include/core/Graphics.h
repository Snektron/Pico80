#ifndef INCLUDE_CORE_GRAPHICS_H_
#define INCLUDE_CORE_GRAPHICS_H_

#include <string>

namespace Graphics
{
	void init(std::string name, int w, int h);
	void destroy();
	void update();

	int getWidth();
	int getHeight();
}

#endif /* INCLUDE_CORE_GRAPHICS_H_ */

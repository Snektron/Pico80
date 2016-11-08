#ifndef INCLUDE_CORE_GRAPHICS_H_
#define INCLUDE_CORE_GRAPHICS_H_

#include <nanovg.h>
#include <string>

namespace Graphics
{
	void init(std::string name, int w, int h);
	void destroy();
	void update();

	int getWidth();
	int getHeight();
	float getPixelRatio();

	NVGcontext* nvg();
}

#endif /* INCLUDE_CORE_GRAPHICS_H_ */

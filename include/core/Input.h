#ifndef INCLUDE_CORE_INPUT_H_
#define INCLUDE_CORE_INPUT_H_

#include <SDL2/SDL.h>

namespace Input
{
	void update();
	void handleEvent(SDL_Event* event);
	bool quitRequested();
}

#endif /* INCLUDE_CORE_INPUT_H_ */

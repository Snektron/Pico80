#ifndef INCLUDE_CORE_INPUT_H_
#define INCLUDE_CORE_INPUT_H_

#include <SDL2/SDL.h>

#define MOUSE_BTN_LEFT 0
#define MOUSE_BTN_RIGHT 1
#define MOUSE_BTN_MIDDLE 2

namespace Input
{
	void update();
	void handleEvent(SDL_Event* event);
	bool quitRequested();

	// thread safe mouse access
	namespace Mouse
	{
		int X();
		int Y();
		int State();
	}
}

#endif /* INCLUDE_CORE_INPUT_H_ */

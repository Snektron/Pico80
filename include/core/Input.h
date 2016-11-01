#ifndef INCLUDE_CORE_INPUT_H_
#define INCLUDE_CORE_INPUT_H_

#include <memory>
#include <SDL2/SDL.h>

#define MOUSE_BTN_LEFT 0
#define MOUSE_BTN_RIGHT 1
#define MOUSE_BTN_MIDDLE 2

namespace Input
{
	void update();
	void handleEvent(SDL_Event* event);
	bool quit_requested();

	// thread safe mouse access
	namespace Mouse
	{
		int X();
		int Y();
		int State();
	}

	namespace Keyboard
	{
		class F12Handler
		{
		public:
			virtual void handle() = 0;
			virtual ~F12Handler() = default;
		};

		void handleKeyboardEvent(SDL_Event *event, bool down);
		uint8_t getLastKey();
		uint8_t getModifiers();
		void setF12Handler(std::weak_ptr<F12Handler> handler);
		int mapKey(SDL_Keysym *sym);
	}
}

#endif /* INCLUDE_CORE_INPUT_H_ */

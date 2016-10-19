#include "core/Input.h"
#include <atomic>
#include <SDL2/SDL.h>
#include "core/Logger.h"
#include "core/Graphics.h"

#define TAG "Input"

namespace
{
	std::atomic<bool> quit(false);
	std::atomic<int> mouseX(0);
	std::atomic<int> mouseY(0);
	std::atomic<int> mouseState(0);
}

namespace Input
{
	void update()
	{
		SDL_Event event;
		while(SDL_PollEvent(&event) != 0)
			handleEvent(&event);
		int x, y;
		uint32_t state = SDL_GetMouseState(&x, &y);
		mouseX = x;
		mouseY = y;

		mouseState |= ((state >> (SDL_BUTTON_LEFT - 1)) & 1) << MOUSE_BTN_LEFT;
		mouseState |= ((state >> (SDL_BUTTON_RIGHT - 1)) & 1) << MOUSE_BTN_RIGHT;
		mouseState |= ((state >> (SDL_BUTTON_MIDDLE - 1)) & 1) << MOUSE_BTN_MIDDLE;
	}

	void handleEvent(SDL_Event* event)
	{
		switch(event->type)
		{
		case SDL_QUIT:
			Logger::info(TAG, "Requesting quit");
			quit = true;
			break;
		case SDL_WINDOWEVENT:
			if (event->window.event == SDL_WINDOWEVENT_RESIZED)
			{
				Logger::info(TAG) << "Window resized: "
						<< event->window.data1 << "x"
						<< event->window.data2 << Logger::endl;
				Graphics::refresh_surface();
			}
		}
	}

	bool quitRequested()
	{
		return quit;
	}

	namespace Mouse
	{
		int X()
		{
			return mouseX;
		}

		int Y()
		{
			return mouseY;
		}

		int State()
		{
			return mouseState;
		}
	}
}

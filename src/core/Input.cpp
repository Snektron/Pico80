#include "core/Input.h"
#include <atomic>
#include <cstdint>
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

	std::mutex keymutex;
	std::array<bool, 0x100> keys({0});
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
				Graphics::refresh_surface();
			break;
		case SDL_KEYDOWN:
			Keyboard::handleKeyboardEvent(event, true);
			break;
		case SDL_KEYUP:
			Keyboard::handleKeyboardEvent(event, false);
			break;
		}
	}

	bool quit_requested()
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

	namespace Keyboard
	{
		void handleKeyboardEvent(SDL_Event *event, bool down)
		{
			std::lock_guard<std::mutex> lock(keymutex);
			switch(event->key.keysym.sym)
			{
			case SDLK_RETURN:
				break;
			}
		}

		bool getKeyState(uint8_t key)
		{
			std::lock_guard<std::mutex> lock(keymutex);
			return keys[key];
		}
	}
}

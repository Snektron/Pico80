#include "core/Input.h"
#include <atomic>
#include <cstdint>
#include <SDL2/SDL.h>
#include "core/Logger.h"
#include "core/Graphics.h"
#include "core/Keys.h"

#define TAG "Input"

namespace
{
	std::atomic<bool> quit(false);
	std::atomic<int> mouseX(0);
	std::atomic<int> mouseY(0);
	std::atomic<int> mouseState(0);

	std::mutex keymutex;
	std::array<bool, 0x100> keys({0});
	std::atomic<bool> f12(false);
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
			if (event->key.keysym.sym == SDLK_F12)
			{
				f12 = true;
				return;
			}
			std::lock_guard<std::mutex> lock(keymutex);

			int key = mapKey(&event->key.keysym);
			if (key)
				keys[key] = down;
		}

		bool getKeyState(uint8_t key)
		{
			std::lock_guard<std::mutex> lock(keymutex);
			return keys[key];
		}

		bool getF12State()
		{
			return f12;
		}

		// map sdl key to internal K_* key
		int mapKey(SDL_Keysym *sym)
		{
			const int shift_mask = KMOD_SHIFT | KMOD_CAPS;
			int k = sym->sym;
			int m = sym->mod;
			switch(k)
			{
			case SDLK_F1:
				return K_F1;
			case SDLK_F2:
				return K_F2;
			case SDLK_F3:
				return K_F3;
			case SDLK_F4:
				return K_F4;
			case SDLK_F5:
				return K_F5;

			case SDLK_DOWN:
				return K_DOWN;
			case SDLK_LEFT:
				return K_LEFT;
			case SDLK_RIGHT:
				return K_RIGHT;
			case SDLK_UP:
				return K_UP;

			case SDLK_BACKSPACE:
				return K_BACKSPACE;
			case SDLK_ESCAPE:
				return K_ESC;
			case SDLK_LSHIFT:
			case SDLK_RSHIFT:
				return K_SHIFT;
			case SDLK_LCTRL:
			case SDLK_RCTRL:
				return K_CTRL;
			case SDLK_SPACE:
				return K_SPACE;
			case SDLK_RETURN:
				return K_ENTER;

			case SDLK_PLUS:
			case SDLK_KP_PLUS:
				return K_PLUS;
			case SDLK_MINUS:
			case SDLK_KP_MINUS:
				return m & KMOD_ALT ? K_NEGATIVE : K_MINUS;
			case SDLK_ASTERISK:
			case SDLK_KP_MULTIPLY:
				return K_ASTERISK;
			case SDLK_SLASH:
			case SDLK_KP_DIVIDE:
				return K_SLASH;
			case SDLK_EQUALS:
			case SDLK_KP_EQUALS:
				return K_EQUALS;

			case SDLK_KP_LEFTBRACE:
				return K_LBRACE;
			case SDLK_KP_RIGHTBRACE:
				return K_LBRACE;
			case SDLK_LEFTBRACKET:
				return m & shift_mask ? K_LBRACE : K_LBRACKET;
			case SDLK_RIGHTBRACKET:
				return m & shift_mask ? K_RBRACE : K_RBRACKET;
			case SDLK_LEFTPAREN:
			case SDLK_KP_LEFTPAREN:
				return K_LPAREN;
			case SDLK_RIGHTPAREN:
			case SDLK_KP_RIGHTPAREN:
				return K_RPAREN;

			case SDLK_UNDERSCORE:
				return K_UNDERSCORE;
			case SDLK_QUESTION:
				return K_QUESTION;
			case SDLK_PERIOD:
				return K_PERIOD;
			case SDLK_COMMA:
				return K_COMMA;
			case SDLK_EXCLAIM:
				return K_EXCLAIM;
			case SDLK_COLON:
				return K_COLON;
			case SDLK_DELETE:
				return K_DEL;
			case SDLK_INSERT:
				return K_INS;
			case SDLK_QUOTE:
				return K_QUOTE;
			case SDLK_QUOTEDBL:
				return SDLK_QUOTEDBL;
			}

			if (m & KMOD_ALT)
			{
				if (k == SDLK_q)
					return K_QUIT;
				else if (k == SDLK_m)
					return K_MODE;
			}

			if (SDLK_a <= k && k <= SDLK_z)
				return k - SDLK_a + (m & shift_mask ? K_A : K_a);
			else if (SDLK_0 <= k && k <= SDLK_9)
				return k - SDLK_0 + K_0;

			return 0;
		}
	}
}

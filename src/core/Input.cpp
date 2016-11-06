#include "core/Input.h"
#include <cstdint>
#include <memory>
#include "core/Logger.h"
#include "core/Keys.h"

#define TAG "Input"

namespace Input
{
	namespace
	{
		bool quit(false);
		int mouseX(0), mouseY(0), mouseState(0);
		uint8_t lastkey(K_NONE), lastmod(0);
		bool f12down(false);
	}

	void mouseCallback(GLFWwindow* window, double x, double y)
	{
		mouseX = (int) x;
		mouseY = (int) y;
	}

	void closeCallback(GLFWwindow* window)
	{
		quit = true;
	}

	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		lastmod = 0;
		if (mods & GLFW_MOD_CONTROL)
			lastmod |= KM_CTRL;
		if (mods & GLFW_MOD_SHIFT)
			lastmod |= KM_SHIFT;
		if (mods & GLFW_MOD_ALT)
			lastmod |= KM_ALT;

		if (key == GLFW_KEY_F12 && action != GLFW_REPEAT)
		{
			f12down = action == GLFW_PRESS;
			return;
		}

		int k = Keyboard::mapKey(key, lastmod);

		if (action == GLFW_RELEASE && key == lastkey)
			lastkey = K_NONE;
		else if (action == GLFW_PRESS)
			lastkey = key;
	}

	void init(GLFWwindow* window)
	{
		glfwSetCursorPosCallback(window, mouseCallback);
		glfwSetWindowCloseCallback(window, closeCallback);
		glfwSetKeyCallback(window, keyCallback);
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

		int state()
		{
			return mouseState;
		}
	}

	namespace Keyboard
	{
		uint8_t getLastKey()
		{
			return lastkey;
		}

		uint8_t getModifiers()
		{
			return lastmod;
		}

		bool wasF12Pressed()
		{
			bool down = f12down;
			f12down = false;
			return down;
		}

		// map sdl key to internal K_* key
		int mapKey(int k, int m)
		{
			if (m & KM_CTRL)
			{
				switch(k)
				{
				case GLFW_KEY_Q:
					return K_QUIT;
				case GLFW_KEY_M:
					return K_MODE;
				case GLFW_KEY_MINUS:
				case GLFW_KEY_KP_SUBTRACT:
					return K_NEGATIVE;
				}
			}
			else if (m & KM_SHIFT)
			{
				switch(k)
				{
				case GLFW_KEY_LEFT_BRACKET:
					return K_LBRACE;
				case GLFW_KEY_RIGHT_BRACKET:
					return K_RBRACE;
				case GLFW_KEY_9:
					return K_LPAREN;
				case GLFW_KEY_0:
					return K_RPAREN;
				case GLFW_KEY_MINUS:
					return K_UNDERSCORE;
				case GLFW_KEY_EQUAL:
					return K_PLUS;
				case GLFW_KEY_8:
					return K_ASTERISK;
				case GLFW_KEY_SLASH:
					return K_QUESTION;
				case GLFW_KEY_1:
					return K_EXCLAIM;
				case GLFW_KEY_SEMICOLON:
					return K_COLON;
				case GLFW_KEY_APOSTROPHE:
					return K_QUOTEDBL;
				default:
					if (GLFW_KEY_A <= k && k <= GLFW_KEY_Z)
						return k - GLFW_KEY_A + K_A;
				}
			}
			else
			{
				switch(k)
				{
				case GLFW_KEY_F1:
					return K_F1;
				case GLFW_KEY_F2:
					return K_F2;
				case GLFW_KEY_F3:
					return K_F3;
				case GLFW_KEY_F4:
					return K_F4;
				case GLFW_KEY_F5:
					return K_F5;

				case GLFW_KEY_DOWN:
					return K_DOWN;
				case GLFW_KEY_LEFT:
					return K_LEFT;
				case GLFW_KEY_RIGHT:
					return K_RIGHT;
				case GLFW_KEY_UP:
					return K_UP;

				case GLFW_KEY_BACKSPACE:
					return K_BACKSPACE;
				case GLFW_KEY_ESCAPE:
					return K_ESC;
				case GLFW_KEY_LEFT_SHIFT:
				case GLFW_KEY_RIGHT_SHIFT:
					return K_SHIFT;
				case GLFW_KEY_LEFT_CONTROL:
				case GLFW_KEY_RIGHT_CONTROL:
					return K_CTRL;
				case GLFW_KEY_SPACE:
					return K_SPACE;
				case GLFW_KEY_ENTER:
				case GLFW_KEY_KP_ENTER:
					return K_ENTER;

				case GLFW_KEY_KP_ADD:
					return K_PLUS;
				case GLFW_KEY_MINUS:
				case GLFW_KEY_KP_SUBTRACT:
					return K_MINUS;
				case GLFW_KEY_KP_MULTIPLY:
					return K_ASTERISK;
				case GLFW_KEY_SLASH:
				case GLFW_KEY_KP_DIVIDE:
					return K_SLASH;
				case GLFW_KEY_EQUAL:
				case GLFW_KEY_KP_EQUAL:
					return K_EQUALS;

				case GLFW_KEY_LEFT_BRACKET:
					return K_LBRACKET;
				case GLFW_KEY_RIGHT_BRACKET:
					return K_RBRACKET;

				case GLFW_KEY_PERIOD:
					return K_PERIOD;
				case GLFW_KEY_COMMA:
					return K_COMMA;
				case GLFW_KEY_DELETE:
					return K_DEL;
				case GLFW_KEY_INSERT:
					return K_INS;
				case GLFW_KEY_APOSTROPHE:
					return K_QUOTE;
				default:
					if (GLFW_KEY_A <= k && k <= GLFW_KEY_Z)
						return k - GLFW_KEY_A + K_a;
					else if (GLFW_KEY_0 <= k && k <= GLFW_KEY_9)
						return k - GLFW_KEY_0 + K_0;
					else
						return K_NONE;
				}
			}

			return K_NONE;
		}
	}
}

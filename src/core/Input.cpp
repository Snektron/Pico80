#include "core/Input.h"
#include <cstdint>
#include <memory>
#include "core/Logger.h"
#include "core/Keys.h"
#include "core/Event.h"
#include "core/Engine.h"

#define TAG "Input"

namespace Input
{
	void mouseMoveCallback(GLFWwindow* window, double x, double y)
	{
		int down = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
		MouseMoveEvent event = {down == GLFW_PRESS ? MOUSE_DRAG : MOUSE_MOVE, (int) x, (int) y, (int) x, (int) y};
		Engine::mouseMoveEvent(event);
	}

	void mouseClickCallback(GLFWwindow* window, int button, int action, int mods)
	{
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		MouseButtonEvent event = {action == GLFW_PRESS ? MOUSE_PRESS : MOUSE_RELEASE, button, (int) x, (int) y, (int) x, (int) y};
		Engine::mouseButtonEvent(event);
	}

	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		KeyAction kaction;
		switch(action)
		{
		case GLFW_PRESS:
			kaction = KEY_PRESS;
			break;
		case GLFW_RELEASE:
			kaction = KEY_RELEASE;
			break;
		case GLFW_REPEAT:
			kaction = KEY_REPEAT;
			break;
		}

		KeyEvent event = {kaction, key, mods};
		Engine::keyEvent(event);
	}

	void closeCallback(GLFWwindow* window)
	{
		Engine::stop();
	}

	void init(GLFWwindow* window)
	{
		glfwSetCursorPosCallback(window, mouseMoveCallback);
		glfwSetMouseButtonCallback(window, mouseClickCallback);
		glfwSetKeyCallback(window, keyCallback);
		glfwSetWindowCloseCallback(window, closeCallback);
	}

	// map glfw key to internal K_* key
	// TODO move this
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

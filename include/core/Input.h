#ifndef INCLUDE_CORE_INPUT_H_
#define INCLUDE_CORE_INPUT_H_

#include <GLFW/glfw3.h>

#define MOUSE_BTN_LEFT 0
#define MOUSE_BTN_RIGHT 1
#define MOUSE_BTN_MIDDLE 2

namespace Input
{
	void init(GLFWwindow* window);
	bool quit_requested();

	namespace Mouse
	{
		int X();
		int Y();
		int state();
	}

	namespace Keyboard
	{
		uint8_t getLastKey();
		uint8_t getModifiers();
		bool wasF12Pressed();
		int mapKey(int k, int m);
	}
}

#endif /* INCLUDE_CORE_INPUT_H_ */

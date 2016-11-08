#ifndef INCLUDE_CORE_EVENT_H_
#define INCLUDE_CORE_EVENT_H_

enum MouseAction
{
	MOUSE_PRESS,
	MOUSE_RELEASE,
	MOUSE_MOVE
};

typedef struct
{
	MouseAction action;
	int button;
	int gx, gy; // global mouse position
	int x, y; // localized mouse position
} MouseEvent;

enum KeyAction
{
	KEY_PRESS,
	KEY_RELEASE,
	KEY_REPEAT
};

typedef struct
{
	KeyAction action;
	int Key;
	int mods;
} KeyEvent;

#endif /* INCLUDE_CORE_EVENT_H_ */

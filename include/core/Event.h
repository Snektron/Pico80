#ifndef INCLUDE_CORE_EVENT_H_
#define INCLUDE_CORE_EVENT_H_

enum MouseButtonAction
{
	MOUSE_PRESS,
	MOUSE_RELEASE
};

typedef struct
{
	MouseButtonAction action;
	int button;
	int gx, gy; // global mouse position
	int x, y; // localized mouse position
} MouseButtonEvent;

enum MouseMoveAction
{
	MOUSE_MOVE,
	MOUSE_DRAG
};

typedef struct
{
	MouseMoveAction action;
	int gx, gy; // global mouse position
	int x, y; // localized mouse position
} MouseMoveEvent;

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

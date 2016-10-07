#ifndef INCLUDE_EMU_DEVICE_MOUSE_H_
#define INCLUDE_EMU_DEVICE_MOUSE_H_

#include <cstdint>
#include "z80e/z80e.h"
#include "emu/device/Screen.h"

#define MOUSE_BTN_LEFT 0
#define MOUSE_BTN_RIGHT 1
#define MOUSE_BTN_MIDDLE 2


class MouseDevice : public Z80e::IODevice
{
protected:
	Screen *screen;

public:
	MouseDevice(Screen *screen);

	void write(uint8_t value);
	virtual uint8_t read() = 0;
	virtual ~MouseDevice() = default;
};

class MouseX : public MouseDevice
{
public:
	MouseX(Screen *screen): MouseDevice(screen){}
	uint8_t read();
};

class MouseY : public MouseDevice
{
public:
	MouseY(Screen *screen): MouseDevice(screen){}
	uint8_t read();
};

class MouseState : public Z80e::IODevice
{
public:
	void write(uint8_t value);
	uint8_t read();
};

class Mouse
{
private:
	MouseX x;
	MouseY y;
	MouseState state;

public:
	Mouse(Screen *screen);
	MouseX* get_mouse_x();
	MouseY* get_mouse_y();
	MouseState* get_mouse_state();
};

#endif /* INCLUDE_EMU_DEVICE_MOUSE_H_ */

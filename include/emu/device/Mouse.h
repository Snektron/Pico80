#ifndef INCLUDE_EMU_DEVICE_MOUSE_H_
#define INCLUDE_EMU_DEVICE_MOUSE_H_

#include <cstdint>
#include <memory>
#include "z80e/z80e.h"
#include "emu/device/Screen.h"

class MouseDevice : public Z80e::IODevice
{
public:
	void write(uint8_t value);
	virtual uint8_t read() = 0;
	virtual ~MouseDevice() = default;
};

class MouseX : public MouseDevice
{
public:
	uint8_t read();
};

class MouseY : public MouseDevice
{
public:
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
	std::shared_ptr<MouseX> x;
	std::shared_ptr<MouseY> y;
	std::shared_ptr<MouseState> state;

public:
	Mouse();
	std::shared_ptr<MouseX> get_mouse_x();
	std::shared_ptr<MouseY> get_mouse_y();
	std::shared_ptr<MouseState> get_mouse_state();
};

#endif /* INCLUDE_EMU_DEVICE_MOUSE_H_ */

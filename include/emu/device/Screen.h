#ifndef INCLUDE_EMU_DEVICE_SCREEN_H_
#define INCLUDE_EMU_DEVICE_SCREEN_H_

#include <cstdint>
#include <memory>
#include <SDL2/SDL.h>
#include "z80e/z80e.h"
#include "core/Display.h"

#define SC_SYNC 0
#define SC_CLEAR 1
#define SC_SET_PIXEL 2
#define SC_GET_PIXEL 3

class Screen : public Z80e::IODevice
{
private:
	std::shared_ptr<Z80e::BasicIODevice> arg0, arg1, arg2;
	uint8_t vram[DISPLAY_WIDTH * DISPLAY_HEIGHT];

public:
	Screen();

	void write(uint8_t value); // screen command port
	uint8_t read();

	void sync();
	void clear(uint8_t color);
	void set_pixel(uint8_t x, uint8_t y, uint8_t color);
	uint8_t get_pixel(uint8_t x, uint8_t y);

	std::shared_ptr<Z80e::BasicIODevice> get_arg0();
	std::shared_ptr<Z80e::BasicIODevice> get_arg1();
	std::shared_ptr<Z80e::BasicIODevice> get_arg2();
};

#endif /* INCLUDE_EMU_DEVICE_SCREEN_H_ */

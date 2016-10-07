#ifndef INCLUDE_EMU_DEVICE_SCREEN_H_
#define INCLUDE_EMU_DEVICE_SCREEN_H_

#include <SDL2/SDL.h>
#include <cstdint>
#include "z80e/z80e.h"

#define SC_SYNC 0
#define SC_CLEAR 1
#define SC_SET_PIXEL 2
#define SC_GET_PIXEL 3

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 128

class Screen : public Z80e::IODevice
{
private:
	SDL_Surface *display;
	Z80e::BasicIODevice arg0, arg1, arg2;
	uint8_t vram[SCREEN_WIDTH * SCREEN_HEIGHT];

public:
	Screen();
	~Screen();

	void get_screen_rect(SDL_Rect& rect);
	void render();

	void write(uint8_t value); // screen command port
	uint8_t read();

	void sync();
	void clear(uint8_t color);
	void set_pixel(uint8_t x, uint8_t y, uint8_t color);
	uint8_t get_pixel(uint8_t x, uint8_t y);

	uint32_t palcol(uint8_t index);

	Z80e::BasicIODevice* get_arg0();
	Z80e::BasicIODevice* get_arg1();
	Z80e::BasicIODevice* get_arg2();
};

#endif /* INCLUDE_EMU_DEVICE_SCREEN_H_ */

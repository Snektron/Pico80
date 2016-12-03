#ifndef INCLUDE_EMU_DEVICE_SCREEN_H_
#define INCLUDE_EMU_DEVICE_SCREEN_H_

#include <cstdint>
#include <memory>
#include <QObject>
#include "z80e/z80e.h"
#include "emu/pico80/Platform.h"

#define SCREEN_INDEX(x, y) (SCREEN_WIDTH * (y & 0x7F) + (x & 0x7F))

#define SC_SYNC 0
#define SC_INVALIDATE 0
#define SC_CLEAR 1
#define SC_SET_PIXEL 2
#define SC_GET_PIXEL 3

class Vram
{
private:
	uint8_t data[SCREEN_WIDTH * SCREEN_HEIGHT];
public:
	void clear(uint8_t color);
	void setPixel(uint8_t x, uint8_t y, uint8_t color);
	uint8_t getPixel(uint8_t x, uint8_t y);
	uint8_t* rawData();
};

class Screen: public QObject, public Z80e::IODevice
{
	Q_OBJECT
public:
	std::shared_ptr<Z80e::BasicIODevice> arg0, arg1, arg2;
	Vram *vram;
public:
	Screen();
	~Screen();

	void write(uint8_t value); // screen command port
	uint8_t read();

	std::shared_ptr<Z80e::BasicIODevice> get_arg0();
	std::shared_ptr<Z80e::BasicIODevice> get_arg1();
	std::shared_ptr<Z80e::BasicIODevice> get_arg2();

signals:
	void invalidate(Vram *vram);
};

#endif /* INCLUDE_EMU_DEVICE_SCREEN_H_ */

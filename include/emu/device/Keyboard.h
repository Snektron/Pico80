#ifndef INCLUDE_EMU_DEVICE_KEYBOARD_H_
#define INCLUDE_EMU_DEVICE_KEYBOARD_H_

#include <cstdint>
#include "z80e/z80e.h"

class Keyboard : public Z80e::IODevice
{
public:
	void write(uint8_t value);
	uint8_t read();
};

class KeyModifiers : public Z80e::IODevice
{
public:
	void write(uint8_t value);
	uint8_t read();
};

class KeyPad : public Z80e::IODevice
{
private:
	uint8_t mapKos(uint8_t key, uint8_t mod);
public:
	void write(uint8_t value);
	uint8_t read();
};

#endif /* INCLUDE_EMU_DEVICE_KEYBOARD_H_ */

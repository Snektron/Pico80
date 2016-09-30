#ifndef INCLUDE_EMU_ASIC_H_
#define INCLUDE_EMU_ASIC_H_

#include "core/Time.h"
#include "z80e/z80e.h"
#include "emu/memory/Memory.h"
#include "emu/device/Screen.h"
#include "emu/device/Log.h"

#define PORT_LOG_OUT 0

#define PORT_MEM_BANK_A 1
#define PORT_MEM_BANK_B 2
#define PORT_MEM_BANK_C 3

#define PORT_SCRN_CMD 4
#define PORT_SCRN_REG_X 5
#define PORT_SCRN_REG_Y 6
#define PORT_SCRN_REG_COLOR 7

class Asic : public Time::TimerCallback
{
private:
	Time::nanoseconds last;

	Memory *memory;
	Screen *screen;
	Log *log;

	Z80e::CPU *cpu;
public:
	Asic();
	void trigger();
	void render();
	void interrupt();
	~Asic();
};

#endif /* INCLUDE_EMU_ASIC_H_ */

#ifndef INCLUDE_EMU_ASIC_H_
#define INCLUDE_EMU_ASIC_H_

#include "core/Time.h"
#include "z80e/z80e.h"
#include "emu/memory/Memory.h"
#include "emu/device/Screen.h"
#include "emu/device/Log.h"
#include "emu/interrupt/Interrupt.h"
#include "interrupt/TimerInt.h"

#define CLOCK_RATE 50000000
#define CLOCK_FREQ 500

#define TIMER_0_FREQ 200

#define PORT_LOG_OUT 0

#define PORT_MEM_BANK_A 1
#define PORT_MEM_BANK_B 2
#define PORT_MEM_BANK_C 3

#define PORT_INT_MASK 4
#define PORT_INT_ACK 5

#define PORT_SCRN_CMD 6
#define PORT_SCRN_REG_X 7
#define PORT_SCRN_REG_Y 8
#define PORT_SCRN_REG_COLOR 9

class Asic : public Time::TimerCallback
{
private:
	Time::nanoseconds last;

	Memory *memory;
	Screen *screen;
	Log *log;

	Interrupt *interrupt;
	TimerInt *timer0;

	Z80e::CPU *cpu;
public:
	Asic();
	void trigger();
	void render();
	void set_interrupt();
	void reset_interrupt();
	TimerInt* get_timer_0();
	~Asic();
};

#endif /* INCLUDE_EMU_ASIC_H_ */

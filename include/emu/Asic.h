#ifndef INCLUDE_EMU_ASIC_H_
#define INCLUDE_EMU_ASIC_H_

#include "core/Time.h"
#include "z80e/z80e.h"
#include "emu/memory/Memory.h"
#include "emu/device/Screen.h"
#include "emu/device/Log.h"
#include "emu/device/Mouse.h"
#include "emu/device/StorageController.h"
#include "emu/interrupt/Interrupt.h"
#include "interrupt/TimerInt.h"

#define CLOCK_RATE 50000000
#define CLOCK_FREQ 500

#define TIMER_0_FREQ 1

class Asic : public Time::Interval
{
private:
	Time::point last;

	Memory *memory;
	Screen *screen;
	Log *log;
	Mouse *mouse;
	StorageController *storage_controller;

	Interrupt *interrupt;
	TimerInt *timer0;

	Z80e::CPU *cpu;
public:
	Asic();
	void start();
	void trigger();

	void set_interrupt();
	void reset_interrupt();
	TimerInt* get_timer_0();
	~Asic();
};

#endif /* INCLUDE_EMU_ASIC_H_ */

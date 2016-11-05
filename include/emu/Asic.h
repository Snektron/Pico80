#ifndef INCLUDE_EMU_ASIC_H_
#define INCLUDE_EMU_ASIC_H_

#include "interrupt/TimerInt.h"
#include <memory>
#include "core/Time.h"
#include "emu/interrupt/TimerInt.h"
#include "emu/memory/Memory.h"
#include "emu/device/Screen.h"
#include "emu/device/Log.h"
#include "emu/device/Mouse.h"
#include "emu/device/StorageController.h"
#include "emu/device/Keyboard.h"
#include "emu/device/Clock.h"
#include "emu/interrupt/Interrupt.h"

// calculate instructions executed in a certain time (ns)
#define INSTRUCTIONS(clockrate, ns) (clockrate * (ns) / SECOND_IN_NANOS)
#define MHZ(x) (x * 1000000)

class Asic
{
private:
	uint64_t clock_rate;
	uint64_t timer_freq;

	std::shared_ptr<Log> log;
	std::shared_ptr<Screen> screen;
	std::shared_ptr<Mouse> mouse;
	std::shared_ptr<StorageController> storage_controller;
	std::shared_ptr<Keyboard> keyboard;
	std::shared_ptr<KeyModifiers> keyModifiers;
	std::shared_ptr<KeyPad> keypad;
	std::shared_ptr<ClockReg> clock_regs[4];

	std::shared_ptr<Memory> memory;

	std::shared_ptr<Interrupt> interrupt;
	std::shared_ptr<TimerInt> timer_int;
	std::shared_ptr<InterruptDevice> f12_int;

	std::shared_ptr<Z80e::CPU> cpu;

	uint64_t leftover;
public:
	Asic(uint64_t clock_rate, uint64_t timer_freq);
	bool tick(uint64_t ticks);
	void f12int();
	uint64_t get_clock_rate();
};

#endif /* INCLUDE_EMU_ASIC_H_ */

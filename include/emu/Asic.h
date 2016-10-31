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
#include "emu/interrupt/Interrupt.h"

#define MHZ(x) (x * 1000000)

#define CLOCK_RATE MHZ(50)
#define CLOCK_FREQ 500

#define TIMER_FREQ 1

class Asic : public Time::Timer
{
private:
	Time::point last;

	std::shared_ptr<Memory> memory;
	std::shared_ptr<Screen> screen;
	std::shared_ptr<Log> log;
	std::shared_ptr<Mouse> mouse;
	std::shared_ptr<StorageController> storage_controller;

	std::shared_ptr<Z80e::CPU> cpu;

	std::shared_ptr<Interrupt> interrupt;
	std::shared_ptr<TimerInt> timer_int;
	std::shared_ptr<InterruptDevice> f12_int;
public:
	Asic();

	void start();
	bool trigger();
};

#endif /* INCLUDE_EMU_ASIC_H_ */

#ifndef INCLUDE_EMU_ASIC_H_
#define INCLUDE_EMU_ASIC_H_

#include "interrupt/TimerInt.h"
#include <memory>
#include <atomic>
#include "core/Time.h"
#include "core/Input.h"
#include "emu/interrupt/TimerInt.h"
#include "emu/memory/Memory.h"
#include "emu/device/Screen.h"
#include "emu/device/Log.h"
#include "emu/device/Mouse.h"
#include "emu/device/Keyboard.h"
#include "emu/device/StorageController.h"
#include "emu/interrupt/Interrupt.h"

#define MHZ(x) (x * 1000000)

#define CLOCK_RATE MHZ(50)
#define CLOCK_FREQ 1000

#define TIMER_FREQ 200

class Asic : public Time::Timer, public Input::Keyboard::F12Handler
{
private:
	Time::point last;

	std::shared_ptr<Log> log;
	std::shared_ptr<Screen> screen;
	std::shared_ptr<Mouse> mouse;
	std::shared_ptr<StorageController> storage_controller;
	std::shared_ptr<Keyboard> keyboard;
	std::shared_ptr<KeyModifiers> keyModifiers;
	std::shared_ptr<KeyPad> keypad;

	std::shared_ptr<Memory> memory;

	std::shared_ptr<Interrupt> interrupt;
	std::shared_ptr<TimerInt> timer_int;
	std::shared_ptr<InterruptDevice> f12_int;

	std::shared_ptr<Z80e::CPU> cpu;

	uint64_t leftover;
	uint64_t totalcycles;
	uint64_t totalticks;
public:
	Asic();

	void start();
	void stop_();
	bool trigger();

	void handle();
};

#endif /* INCLUDE_EMU_ASIC_H_ */

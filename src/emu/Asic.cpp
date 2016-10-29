#include "emu/Asic.h"
#include <cstdint>
#include <chrono>
#include <memory>
#include "core/Time.h"
#include "core/Logger.h"
#include "emu/Ports.h"
#include "emu/interrupt/TimerInt.h"
#include "emu/memory/Memory.h"
#include "emu/device/Screen.h"
#include "emu/device/Log.h"
#include "emu/device/Mouse.h"
#include "emu/device/StorageController.h"
#include "emu/interrupt/Interrupt.h"

#define TAG "Asic"

// calculate instructions executed in a certain time (ns)
#define INSTRUCTIONS(ns) (CLOCK_RATE * (ns) / SECOND_IN_NANOS)

Asic::Asic():
	Time::Timer(Time::nanoseconds(SECOND_IN_NANOS/CLOCK_FREQ))
{
	Logger::info(TAG, "Initializing asic");
	Logger::info(TAG) << "Clock rate: " << CLOCK_RATE/1000000.0 << " Mhz" << Logger::endl;
	Logger::info(TAG) << "Clock freq: " << CLOCK_FREQ << " hz" << Logger::endl;

	storage_controller = std::make_shared<StorageController>();

	memory = std::make_shared<Memory>(storage_controller);
	memory->get_bank(BANK_0)->write(0);
	memory->get_bank(BANK_A)->write(0);
	memory->get_bank(BANK_B)->write(RAM_PAGE(0));
	memory->get_bank(BANK_C)->write(RAM_PAGE(1));

	screen = std::make_shared<Screen>();
	log = std::make_shared<Log>();
	mouse = std::make_shared<Mouse>();

	cpu = std::make_shared<Z80e::CPU>(memory);

	interrupt = std::make_shared<Interrupt>(cpu);
	timer_int = std::make_shared<TimerInt>(interrupt, INT_TIMER, INSTRUCTIONS(SECOND_IN_NANOS / TIMER_FREQ));

	cpu->add_device(PORT_LOG_OUT, log);

	cpu->add_device(PORT_MEM_BANK_A, memory->get_bank(BANK_A));
	cpu->add_device(PORT_MEM_BANK_B, memory->get_bank(BANK_B));
	cpu->add_device(PORT_MEM_BANK_C, memory->get_bank(BANK_C));

	cpu->add_device(PORT_INT_MASK, interrupt->get_interrupt_mask());
	cpu->add_device(PORT_INT_ACK, interrupt);

	cpu->add_device(PORT_SCRN_CMD, screen);
	cpu->add_device(PORT_SCRN_ARG0, screen->get_arg0());
	cpu->add_device(PORT_SCRN_ARG1, screen->get_arg1());
	cpu->add_device(PORT_SCRN_ARG2, screen->get_arg2());

	cpu->add_device(PORT_MOUSE_X, mouse->get_mouse_x());
	cpu->add_device(PORT_MOUSE_Y, mouse->get_mouse_y());
	cpu->add_device(PORT_MOUSE_BTN, mouse->get_mouse_state());

	cpu->add_device(PORT_STORAGE_CTRL, storage_controller);
}

void Asic::start()
{
	last = Time::now();
	Time::Timer::start();
}

bool Asic::trigger()
{
	Time::nanoseconds passed = Time::now() - last;
	last = Time::now();
	uint64_t cycles = INSTRUCTIONS(Time::toint(passed));
	uint64_t timer_cycles = timer_int->instructions_to_trigger();

	while (timer_cycles < cycles)
	{
		int executed = timer_cycles - cpu->execute(timer_cycles);
		cycles -= executed;
		timer_int->trigger();
		timer_cycles = timer_int->instructions_to_trigger();
	}

	int executed = cycles - cpu->execute(cycles);
	timer_int->update(executed);
}

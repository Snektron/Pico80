#include "emu/Asic.h"
#include <cstdint>
#include <chrono>
#include <memory>
#include "emu/Platform.h"
#include "core/Time.h"
#include "core/Logger.h"
#include "emu/interrupt/TimerInt.h"
#include "emu/memory/Memory.h"
#include "emu/device/Screen.h"
#include "emu/device/Log.h"
#include "emu/device/Mouse.h"
#include "emu/device/Keyboard.h"
#include "emu/device/StorageController.h"
#include "emu/interrupt/Interrupt.h"

#define TAG "Asic"

Asic::Asic(uint64_t clock_rate, uint64_t timer_freq):
	clock_rate(clock_rate),
	timer_freq(timer_freq)
{
	Logger::info(TAG, "Initializing asic");
	Logger::info(TAG) << "Clock rate: " << clock_rate/1000000.0 << " Mhz" << Logger::endl;
	Logger::info(TAG) << "Clock freq: " << timer_freq << " hz" << Logger::endl;

	log = std::make_shared<Log>();
	screen = std::make_shared<Screen>();
	mouse = std::make_shared<Mouse>();
	storage_controller = std::make_shared<StorageController>();
	keyboard = std::make_shared<Keyboard>();
	keypad = std::make_shared<KeyPad>();
	keyModifiers = std::make_shared<KeyModifiers>();
	for (int i=0; i<4; i++)
		clock_regs[i] = std::make_shared<ClockReg>(i);

	memory = std::make_shared<Memory>(storage_controller);
	memory->get_bank(BANK_0)->write(0);
	memory->get_bank(BANK_A)->write(0);
	memory->get_bank(BANK_B)->write(RAM_PAGE(0));
	memory->get_bank(BANK_C)->write(RAM_PAGE(1));

	interrupt = std::make_shared<Interrupt>();
	timer_int = std::make_shared<TimerInt>(interrupt, INT_TIMER, INSTRUCTIONS(clock_rate, SECOND_IN_NANOS / timer_freq));
	f12_int = std::make_shared<InterruptDevice>(interrupt, INT_F12);

	cpu = std::make_shared<Z80e::CPU>(memory, interrupt);

	cpu->add_device(PORT_LOG_OUT, log);

	cpu->add_device(PORT_MEM_BANK_A, memory->get_bank(BANK_A));
	cpu->add_device(PORT_MEM_BANK_B, memory->get_bank(BANK_B));
	cpu->add_device(PORT_MEM_BANK_C, memory->get_bank(BANK_C));

	cpu->add_device(PORT_INT_MASK, interrupt);
	cpu->add_device(PORT_INT_TRIG, interrupt->get_interrupt_trig());

	cpu->add_device(PORT_SCRN_CMD, screen);
	cpu->add_device(PORT_SCRN_ARG0, screen->get_arg0());
	cpu->add_device(PORT_SCRN_ARG1, screen->get_arg1());
	cpu->add_device(PORT_SCRN_ARG2, screen->get_arg2());

	cpu->add_device(PORT_MOUSE_X, mouse->get_mouse_x());
	cpu->add_device(PORT_MOUSE_Y, mouse->get_mouse_y());
	cpu->add_device(PORT_MOUSE_BTN, mouse->get_mouse_state());

	cpu->add_device(PORT_STORAGE_CTRL, storage_controller);

	cpu->add_device(PORT_KEYBOARD, keyboard);
	cpu->add_device(PORT_KEYPAD, keypad);
	cpu->add_device(PORT_KEYMOD, keyModifiers);

	cpu->add_device(PORT_CLOCKREG1, clock_regs[0]);
	cpu->add_device(PORT_CLOCKREG2, clock_regs[1]);
	cpu->add_device(PORT_CLOCKREG3, clock_regs[2]);
	cpu->add_device(PORT_CLOCKREG4, clock_regs[3]);

	leftover = 0;
}

bool Asic::tick(uint64_t ticks)
{
	uint64_t cycles = ticks + leftover;
	uint64_t timer_cycles = timer_int->instructions_to_trigger();

	while (timer_cycles < cycles)
	{
		int executed = timer_cycles - cpu->execute(timer_cycles);
		cycles -= executed;
		timer_int->trigger();
		timer_cycles = timer_int->instructions_to_trigger();
	}

	leftover = cpu->execute(cycles);
	int executed = cycles - leftover;
	timer_int->update(executed);
	return false;
}

void Asic::f12int()
{
	f12_int->trigger();
}

uint64_t Asic::get_clock_rate()
{
	return clock_rate;
}

std::shared_ptr<Screen> Asic::getScreen()
{
	return screen;
}

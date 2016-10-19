#include <cstdint>
#include <chrono>
#include "emu/Asic.h"
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

namespace Asic
{
	namespace
	{
		Time::TimerWrapper timer(trigger, std::chrono::seconds(1));
		Time::point last;

		Memory *memory;
		Screen *screen;
		Log *log;
		Mouse *mouse;
		StorageController *storage_controller;

		Interrupt *interrupt;
		TimerInt *timer0;

		Z80e::CPU *cpu;
	}

	void init()
	{
		Logger::info(TAG, "Initializing asic");
		Logger::info(TAG) << "Clock rate: " << CLOCK_RATE/1000000.0 << " Mhz" << Logger::endl;
		Logger::info(TAG) << "Clock freq: " << CLOCK_FREQ << " hz" << Logger::endl;

		storage_controller = new StorageController();

		memory = new Memory(storage_controller);
		memory->get_bank(BANK_0)->write(0);
		memory->get_bank(BANK_A)->write(0);
		memory->get_bank(BANK_B)->write(RAM_PAGE(0));
		memory->get_bank(BANK_C)->write(RAM_PAGE(1));

		screen = new Screen();
		log = new Log();
		mouse = new Mouse(screen);

		interrupt = new Interrupt();
		timer0 = new TimerInt(interrupt, INT_TIMER, Time::nanoseconds(SECOND_IN_NANOS / TIMER_0_FREQ));

		cpu = new Z80e::CPU(memory);

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

	void start()
	{
		last = Time::now();
		timer.start();
	}

	void stop()
	{
		timer.stop();
	}

	void trigger()
	{
		Time::nanoseconds passed = Time::now() - last;
		last = Time::now();
		uint64_t cycles = CLOCK_RATE * Time::toint(passed) / SECOND_IN_NANOS;
		cpu->execute(cycles);
	}

	void set_interrupt()
	{
		cpu->set_interrupt();
	}

	void reset_interrupt()
	{
		cpu->reset_interrupt();
	}

	TimerInt* get_timer_0()
	{
		return timer0;
	}

	void destroy()
	{
		Logger::info(TAG, "Destroying asic");
		delete cpu;
		delete timer0;
		delete interrupt;

		delete mouse;
		delete log;
		delete screen;
		delete memory;
		delete storage_controller;
	}
}

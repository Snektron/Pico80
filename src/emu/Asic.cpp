#include <cstdint>
#include "emu/Asic.h"

#include "../../include/emu/interrupt/TimerInt.h"
#include "core/Time.h"
#include "core/Logger.h"
#include "emu/memory/Memory.h"
#include "emu/device/Screen.h"
#include "emu/device/Log.h"
#include "emu/interrupt/Interrupt.h"

#define TAG "Asic"

Asic::Asic()
{
	Logger::info(TAG, "Initializing asic");
	Logger::info(TAG) << "Clock rate: " << CLOCK_RATE/1000000.0 << " Mhz" << Logger::endl;
	Logger::info(TAG) << "Clock freq: " << CLOCK_FREQ << " hz" << Logger::endl;
	set_interval(SECOND_IN_NANOS / CLOCK_FREQ);

	last = Time::nanotime();

	memory = new Memory();
	memory->get_bank(BANK_0)->write(0);
	memory->get_bank(BANK_A)->write(0);
	memory->get_bank(BANK_B)->write(0x80);
	memory->get_bank(BANK_C)->write(0x81);

	screen = new Screen();
	log = new Log();

	interrupt = new Interrupt(this);
	timer0 = new TimerInt(interrupt, 0, SECOND_IN_NANOS / TIMER_0_FREQ);

	cpu = new Z80e::CPU(memory);

	cpu->add_device(PORT_LOG_OUT, log);

	cpu->add_device(PORT_MEM_BANK_A, memory->get_bank(BANK_A));
	cpu->add_device(PORT_MEM_BANK_B, memory->get_bank(BANK_B));
	cpu->add_device(PORT_MEM_BANK_C, memory->get_bank(BANK_C));

	cpu->add_device(PORT_INT_MASK, interrupt->get_interrupt_mask());
	cpu->add_device(PORT_INT_ACK, interrupt);

	cpu->add_device(PORT_SCRN_CMD, screen);
	cpu->add_device(PORT_SCRN_REG_X, screen->get_reg_x());
	cpu->add_device(PORT_SCRN_REG_Y, screen->get_reg_y());
	cpu->add_device(PORT_SCRN_REG_COLOR, screen->get_reg_color());
}

void Asic::trigger()
{
	Time::nanoseconds passed = Time::nanotime() - last;
	last = Time::nanotime();
	uint64_t cycles = CLOCK_RATE * Time::nanotoint(passed) / SECOND_IN_NANOS;

	cpu->execute(cycles);
}

void Asic::render()
{
	screen->render();
}

void Asic::set_interrupt()
{
	cpu->set_interrupt();
}

void Asic::reset_interrupt()
{
	cpu->reset_interrupt();
}

TimerInt* Asic::get_timer_0()
{
	return timer0;
}

Asic::~Asic()
{
	Logger::info(TAG, "Destroying asic");
	delete cpu;
	delete memory;
	delete screen;
	delete interrupt;
}

#ifndef INCLUDE_EMU_ASIC_H_
#define INCLUDE_EMU_ASIC_H_

#include <memory>
#include <cstdint>
#include <QObject>
#include "core/Time.h"
#include "emu/api/AbstractAsic.h"
#include "emu/pico80/memory/Memory.h"
#include "emu/pico80/device/Screen.h"
#include "emu/pico80/device/Log.h"
#include "emu/pico80/device/Mouse.h"
#include "emu/pico80/device/StorageController.h"
#include "emu/pico80/device/Keyboard.h"
#include "emu/pico80/device/Clock.h"
#include "emu/pico80/interrupt/Interrupt.h"
#include "emu/pico80/interrupt/TimerInt.h"

// calculate instructions executed in a certain time (ns)
#define INSTRUCTIONS(clockrate, ns) ((clockrate) * (ns) / SECOND_IN_NANOS)
#define MHZ(x) (x * 1000000)

class Asic : public AbstractAsic
{
	Q_OBJECT
private:
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
	std::shared_ptr<InterruptDevice> int_on;

	std::shared_ptr<Z80e::CPU> cpu;

	int leftover;
public:
	Asic(int asic_clock, int timer_freq);
	void tick(int states);
	bool isDisplayDirty();
	AbstractDisplayData* getDisplayData();

public slots:
	void turnOn();
	void keyPress(uint8_t key);

private slots:
	void invalidate(Vram *vram);

signals:
	void screenDirty(Vram *vram);
};

#endif /* INCLUDE_EMU_ASIC_H_ */

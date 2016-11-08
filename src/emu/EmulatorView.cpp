#include "emu/EmulatorView.h"
#include <memory>
#include "emu/Display.h"
#include "emu/Asic.h"
#include "emu/device/Screen.h"

#define TAG "EmulatorView"

EmulatorView::EmulatorView():
	SingleView(std::make_shared<Display>()),
	display(std::dynamic_pointer_cast<Display>(getChild()))
{
	asic = std::make_shared<Asic>(ASIC_CLOCK, ASIC_TIMER);
	last = Time::now();
}

void EmulatorView::onTick()
{
	Time::point time = Time::now();
	Time::nanoseconds passed = time - last;
	last = time;
	uint64_t cycles = INSTRUCTIONS(ASIC_CLOCK, Time::toint(passed));
//TODO	asic->tick(cycles);
}

void EmulatorView::onRender()
{
	std::shared_ptr<Screen> screen = asic->getScreen();
	if (!screen->isValid())
	{
		display->write(screen->getVram());
		screen->validate();
	}

}

#include "emu/EmulatorView.h"
#include <memory>
#include "emu/Display.h"
#include "emu/Asic.h"
#include "emu/device/Screen.h"
#include "core/Logger.h"

#define TAG "EmulatorView"

EmulatorView::EmulatorView()
{
	display = std::make_shared<Display>();
	addChild(display);
	asic = std::make_shared<Asic>(ASIC_CLOCK, ASIC_TIMER);
	last = Time::now();
}

void EmulatorView::onTick()
{
	Time::point time = Time::now();
	Time::nanoseconds passed = time - last;
	last = time;
	uint64_t cycles = INSTRUCTIONS(ASIC_CLOCK, Time::toint(passed));
//FIXME	asic->tick(cycles);
}

void EmulatorView::onRender(NVGcontext *vg)
{
	std::shared_ptr<Screen> screen = asic->getScreen();
	if (!screen->isValid())
	{
		display->write(screen->getVram());
		screen->validate();
	}

	ViewGroup::onRender(vg);
}

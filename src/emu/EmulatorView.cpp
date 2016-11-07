#include "emu/EmulatorView.h"
#include <memory>
#include "core/Display.h"
#include "emu/Asic.h"

#define TAG "EmulatorView"

EmulatorView::EmulatorView()
{
	Display::init();
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

void EmulatorView::onRender(Eigen::Matrix4f matrix)
{
	Display::render();
}

void EmulatorView::onResize(float width, float height)
{

}

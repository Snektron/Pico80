#ifndef INCLUDE_EMU_EMULATORVIEW_H_
#define INCLUDE_EMU_EMULATORVIEW_H_

#include "core/view/SingleView.h"
#include "core/Time.h"
#include "emu/Display.h"
#include "emu/Asic.h"

#define ASIC_CLOCK MHZ(50)
#define ASIC_TIMER 200

class EmulatorView : public SingleView
{
private:
	std::shared_ptr<Display> display;
	std::shared_ptr<Asic> asic;
	Time::point last;

public:
	EmulatorView();
	void onTick();
	void onRender();
};

#endif /* INCLUDE_EMU_EMULATORVIEW_H_ */

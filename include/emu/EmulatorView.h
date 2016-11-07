#ifndef INCLUDE_EMU_EMULATORVIEW_H_
#define INCLUDE_EMU_EMULATORVIEW_H_

#include <eigen3/Eigen/Core>
#include "core/view/View.h"
#include "core/Time.h"
#include "emu/Asic.h"

#define ASIC_CLOCK MHZ(50)
#define ASIC_TIMER 200

class EmulatorView : public View
{
private:
	std::shared_ptr<Asic> asic;
	Time::point last;

public:
	EmulatorView();
	void onTick();
	void onRender(Eigen::Matrix4f matrix);
	void onResize(float width, float height);
};

#endif /* INCLUDE_EMU_EMULATORVIEW_H_ */

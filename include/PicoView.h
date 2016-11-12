#ifndef INCLUDE_PICOVIEW_H_
#define INCLUDE_PICOVIEW_H_

#include "core/view/ViewGroup.h"
#include "emu/EmulatorView.h"

class PicoView : public ViewGroup
{
private:
	std::shared_ptr<EmulatorView> emulator;

public:
	PicoView();
	void onTick();
	void onLayout(const Vector2i& pos, const Vector2i& size);
	void onMouseMoveEvent(MouseMoveEvent& event);
	bool onMouseButtonEvent(MouseButtonEvent& event);
};

#endif /* INCLUDE_PICOVIEW_H_ */

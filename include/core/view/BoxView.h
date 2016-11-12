#ifndef INCLUDE_CORE_VIEW_BOXVIEW_H_
#define INCLUDE_CORE_VIEW_BOXVIEW_H_

#include "core/view/View.h"

class BoxView : public View
{
private:
	NVGcolor color;

public:
	BoxView(NVGcolor color):
		color(color)
	{}

	virtual void onRender(NVGcontext *vg)
	{
		nvgBeginPath(vg);
		nvgRect(vg, getLeft(), getTop(), getWidth(), getHeight());
		nvgFillColor(vg, color);
		nvgFill(vg);
	}
};

#endif /* INCLUDE_CORE_VIEW_BOXVIEW_H_ */

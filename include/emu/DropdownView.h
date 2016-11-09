#ifndef INCLUDE_EMU_DROPDOWNVIEW_H_
#define INCLUDE_EMU_DROPDOWNVIEW_H_

#include "core/view/ViewGroup.h"
#include "core/Logger.h"

class DropdownView : public ViewGroup
{
public:
	DropdownView(ViewPtr child)
	{
		addChild(child);
	}

	virtual void onRender(NVGcontext *vg)
	{
		NVGpaint shadowPaint = nvgBoxGradient(vg, getLeft(), getTop(), getWidth(), getHeight(), 0, 10.0, nvgRGBA(0, 0, 0, 128), nvgRGBA(0, 0, 0, 0));
		nvgBeginPath(vg);
		nvgRect(vg, getLeft() - 10, getTop() - 10, getWidth() + 20, getHeight() + 20);
		nvgRect(vg, getLeft(), getTop(), getWidth(), getHeight());
		nvgPathWinding(vg, NVG_HOLE);
		nvgFillPaint(vg, shadowPaint);
		nvgFill(vg);

		ViewGroup::onRender(vg);
	}
};

#endif /* INCLUDE_EMU_DROPDOWNVIEW_H_ */

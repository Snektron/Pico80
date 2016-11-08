#ifndef INCLUDE_EMU_DROPDOWNVIEW_H_
#define INCLUDE_EMU_DROPDOWNVIEW_H_

#include <nanovg.h>

#include "core/view/UnaryView.h"
#include "core/Graphics.h"
#include "core/Logger.h"

class DropdownView : public UnaryView
{
public:
	DropdownView(ViewPtr child):
		UnaryView(child)
	{}

	virtual void onRender()
	{
		NVGcontext *vg = Graphics::nvg();
		NVGpaint shadowPaint = nvgBoxGradient(vg, x, y, width, height, 0, 10.0, nvgRGBA(0, 0, 0, 200), nvgRGBA(0, 0, 0, 0));
		nvgBeginPath(vg);
		nvgRect(vg, x - 10, y - 10, width + 20, height + 20);
		nvgRect(vg, x, y, width, height);
		nvgPathWinding(vg, NVG_HOLE);
		nvgFillPaint(vg, shadowPaint);
		nvgFill(vg);

		UnaryView::onRender();
	}
};

#endif /* INCLUDE_EMU_DROPDOWNVIEW_H_ */

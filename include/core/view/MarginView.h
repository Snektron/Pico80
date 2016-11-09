#ifndef INCLUDE_CORE_VIEW_MARGINVIEW_H_
#define INCLUDE_CORE_VIEW_MARGINVIEW_H_

#include "core/view/ViewGroup.h"

class MarginView : public ViewGroup
{
protected:
	float mid;

public:
	MarginView(float mid, ViewPtr child):
		mid(mid)
	{
		addChild(child);
	}

	virtual void onLayout(int x, int y, int w, int h)
	{
		View::onLayout(x, y, w, h);

		if (!hasChildren())
			return;

		int newWidth = (int) w * mid;
		int newHeight = (int) h * mid;

		int xdiff = w - newWidth;
		int ydiff = h - newHeight;

		getChild(0)->onLayout(xdiff / 2, ydiff / 2, newWidth, newHeight);
	}

	virtual ~MarginView() = default;
};

#endif /* INCLUDE_CORE_VIEW_MARGINVIEW_H_ */

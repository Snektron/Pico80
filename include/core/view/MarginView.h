#ifndef INCLUDE_CORE_VIEW_MARGINVIEW_H_
#define INCLUDE_CORE_VIEW_MARGINVIEW_H_

#include "core/view/UnaryView.h"

class MarginView : public UnaryView
{
protected:
	float w;

public:
	MarginView(float w, ViewPtr child):
		w(w),
		UnaryView(child)
	{}

	virtual void onLayout(int x, int y, int width, int height)
	{
		UnaryView::onLayout(x, y, width, height);

		int newWidth = (int) width * w;
		int newHeight = (int) height * w;

		int xdiff = width - newWidth;
		int ydiff = height - newHeight;

		child->onLayout(x + xdiff / 2, y + ydiff / 2, newWidth, newHeight);
	}

	virtual ~MarginView() = default;
};

#endif /* INCLUDE_CORE_VIEW_MARGINVIEW_H_ */

#ifndef INCLUDE_CORE_VIEW_RATIOVIEW_H_
#define INCLUDE_CORE_VIEW_RATIOVIEW_H_

#include "core/view/UnaryView.h"

class RatioView : public UnaryView
{
protected:
	float ratio;

public:
	RatioView(float ratio, ViewPtr child):
		ratio(ratio),
		UnaryView(child)
	{}

	virtual void onLayout(int x, int y, int width, int height)
	{
		UnaryView::onLayout(x, y, width, height);

		if ((float) width / (float) height > ratio)
		{
			int newWidth = height * ratio;
			int diff = width - newWidth;
			child->onLayout(x + diff / 2, y, newWidth, height);
		}
		else
		{
			int newHeight = width / ratio;
			int diff = height - newHeight;
			child->onLayout(x, y + diff / 2, width, newHeight);
		}
	}

	virtual ~RatioView() = default;
};

#endif /* INCLUDE_CORE_VIEW_RATIOVIEW_H_ */

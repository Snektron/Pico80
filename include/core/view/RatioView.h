#ifndef INCLUDE_CORE_VIEW_RATIOVIEW_H_
#define INCLUDE_CORE_VIEW_RATIOVIEW_H_

#include "core/view/ViewGroup.h"
#include "core/Logger.h"

class RatioView : public ViewGroup
{
protected:
	float ratio;

public:
	RatioView(float ratio, ViewPtr child):
		ratio(ratio)
	{
		addChild(child);
	}

	virtual void onLayout(int x, int y, int w, int h)
	{
		View::onLayout(x, y, w, h);

		if (!hasChildren())
			return;

		if ((float) w / (float) h > ratio)
		{
			int newWidth = h * ratio;
			int diff = w - newWidth;
			getChild(0)->onLayout(diff / 2, 0, newWidth, h);
		}
		else
		{
			int newHeight = w / ratio;
			int diff = h - newHeight;
			getChild(0)->onLayout(0, diff / 2, w, newHeight);
		}
	}

	virtual ~RatioView() = default;
};

#endif /* INCLUDE_CORE_VIEW_RATIOVIEW_H_ */

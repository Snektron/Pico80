#ifndef INCLUDE_CORE_VIEW_RATIOVIEW_H_
#define INCLUDE_CORE_VIEW_RATIOVIEW_H_

#include "core/view/SingleChildView.h"

class RatioView : public SingleChildView
{
protected:
	float ratio;

public:
	RatioView(float ratio, ViewPtr child):
		ratio(ratio),
		SingleChildView(child)
	{}

	virtual void resize(int x, int y, int width, int height)
	{
		View::resize(x, y, width, height);

		if ((float) width / (float) height > ratio)
		{
			int newWidth = height * ratio;
			int diff = width - newWidth;
			child->resize(x + diff / 2, y, newWidth, height);
		}
		else
		{
			int newHeight = width / ratio;
			int diff = height - newHeight;
			child->resize(x, y - diff / 2, width, newHeight);
		}
	}

	virtual ~RatioView() = default;
};

#endif /* INCLUDE_CORE_VIEW_RATIOVIEW_H_ */

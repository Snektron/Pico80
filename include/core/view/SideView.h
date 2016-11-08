#ifndef INCLUDE_CORE_VIEW_SIDEVIEW_H_
#define INCLUDE_CORE_VIEW_SIDEVIEW_H_

#include "core/view/DualView.h"

class SideView : public DualView
{
protected:
	float ratio;

public:
	SideView(float ratio, ViewPtr a, ViewPtr b):
		ratio(ratio),
		DualView(a, b)
	{}

	void setRatio(float ratio)
	{
		this->ratio = ratio;
		resize(x, y, width, height);
	}

	virtual void resize(int x, int y, int width, int height)
	{
		View::resize(x, y, width, height);

		int newWidth = width / 2;
		a->resize(x, y, newWidth, height);
		b->resize(x + newWidth, y, newWidth, height);
	}

	virtual ~SideView() = default;
};

#endif /* INCLUDE_CORE_VIEW_SIDEVIEW_H_ */

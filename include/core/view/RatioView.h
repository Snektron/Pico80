#ifndef INCLUDE_CORE_VIEW_RATIOVIEW_H_
#define INCLUDE_CORE_VIEW_RATIOVIEW_H_

#include "core/view/ViewGroup.h"

class RatioView : public ViewGroup
{
protected:
	float ratio;

public:
	RatioView(float ratio, View::Ptr child):
		ratio(ratio)
	{
		addChild(child);
	}

	virtual void onLayout(const Vector2i& pos, const Vector2i& size)
	{
		View::onLayout(pos, size);

		if (!hasChildren())
			return;

		if ((float) size.x() / (float) size.y() > ratio)
		{
			int newWidth = size.y() * ratio;
			int diff = size.x() - newWidth;
			getChild(0)->onLayout(Vector2i(diff / 2, 0), Vector2i(newWidth, size.y()));
		}
		else
		{
			int newHeight = size.x() / ratio;
			int diff = size.y() - newHeight;
			getChild(0)->onLayout(Vector2i(0, diff / 2), Vector2i(size.x(), newHeight));
		}
	}

	virtual ~RatioView() = default;
};

#endif /* INCLUDE_CORE_VIEW_RATIOVIEW_H_ */

#ifndef INCLUDE_CORE_VIEW_MARGINVIEW_H_
#define INCLUDE_CORE_VIEW_MARGINVIEW_H_

#include "core/view/ViewGroup.h"

class MarginView : public ViewGroup
{
protected:
	float mid;

public:
	MarginView(float mid, View::Ptr child):
		mid(mid)
	{
		addChild(child);
	}

	virtual void onLayout(const Vector2i& pos, const Vector2i& size)
	{
		View::onLayout(pos, size);

		if (!hasChildren())
			return;

		Vector2i newSize = (size.cast<float>() * mid).cast<int>();
		Vector2i diff = size - newSize;

		getChild(0)->onLayout(diff / 2, newSize);
	}

	virtual ~MarginView() = default;
};

#endif /* INCLUDE_CORE_VIEW_MARGINVIEW_H_ */

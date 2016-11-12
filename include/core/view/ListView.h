#ifndef INCLUDE_CORE_VIEW_LISTVIEW_H_
#define INCLUDE_CORE_VIEW_LISTVIEW_H_

#include "core/view/ViewGroup.h"

class ListView : public ViewGroup
{
public:
	virtual void onLayout(Vector2i& pos, Vector2i& size)
	{
		View::onLayout(pos, size);

		if (!hasChildren())
			return;

		int n = getChildCount(), i = 0;

		for (auto child : children)
		{
			int nt = i * size.y() / n;
			int nb = (i + 1) * size.y() / n;
			child->onLayout(Vector2i(0, nt), Vector2i(size.x(), nb - nt));
			i++;
		}
	}

	virtual ~ListView() = default;
};

#endif /* INCLUDE_CORE_VIEW_LISTVIEW_H_ */

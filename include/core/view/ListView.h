#ifndef INCLUDE_CORE_VIEW_LISTVIEW_H_
#define INCLUDE_CORE_VIEW_LISTVIEW_H_

#include "core/view/ViewGroup.h"

class ListView : public ViewGroup
{
public:
	virtual void onLayout(int x, int y, int w, int h)
	{
		View::onLayout(x, y, w, h);

		if (!hasChildren())
			return;

		int n = getChildCount(), i = 0;

		for (auto child : children)
		{
			int nt = i * h / n;
			int nb = (i + 1) * h / n;
			child->onLayout(0, nt, w, nb - nt);
			i++;
		}
	}

	virtual ~ListView() = default;
};

#endif /* INCLUDE_CORE_VIEW_LISTVIEW_H_ */

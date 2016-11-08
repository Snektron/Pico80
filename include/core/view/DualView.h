#ifndef INCLUDE_CORE_VIEW_DUALVIEW_H_
#define INCLUDE_CORE_VIEW_DUALVIEW_H_

#include "core/view/View.h"

class DualView : public View
{
protected:
	ViewPtr a, b;

public:
	DualView(ViewPtr a, ViewPtr b):
		a(a), b(b)
	{}

	virtual void update()
	{
		View::update();
		a->update();
		b->update();
	}

	virtual void render(Eigen::Matrix4f& mv, Eigen::Matrix4f& p)
	{
		View::render(mv, p);
		a->render(mv, p);
		b->render(mv, p);
	}

	virtual void resize(int x, int y, int width, int height)
	{
		View::resize(x, y, width, height);
		a->resize(x, y, width, height);
		b->resize(x, y, width, height);
	}

	virtual ~DualView() = default;
};

#endif /* INCLUDE_CORE_VIEW_DUALVIEW_H_ */

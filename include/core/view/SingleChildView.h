#ifndef INCLUDE_CORE_VIEW_SINGLECHILDVIEW_H_
#define INCLUDE_CORE_VIEW_SINGLECHILDVIEW_H_

#include "core/view/View.h"

class SingleChildView : public View
{
protected:
	ViewPtr child;

public:
	SingleChildView(ViewPtr child):
		child(child)
	{}

	virtual void update()
	{
		View::update();
		child->update();
	}

	virtual void render(Eigen::Matrix4f& mv, Eigen::Matrix4f& p)
	{
		View::render(mv, p);
		child->render(mv, p);
	}

	virtual void resize(int x, int y, int width, int height)
	{
		View::resize(x, y, width, height);
		child->resize(x, y, width, height);
	}

	virtual ~SingleChildView() = default;
};

#endif /* INCLUDE_CORE_VIEW_SINGLECHILDVIEW_H_ */

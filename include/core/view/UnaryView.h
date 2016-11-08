#ifndef INCLUDE_CORE_VIEW_UNARYVIEW_H_
#define INCLUDE_CORE_VIEW_UNARYVIEW_H_

#include "core/view/View.h"
#include "core/Logger.h"

class UnaryView : public View
{
protected:
	ViewPtr child;

public:
	UnaryView(ViewPtr child):
		child(child)
	{}

	virtual void onUpdate()
	{
		if (child)
			child->onUpdate();
	}

	virtual void onRender()
	{
		if (child)
			child->onRender();
	}

	virtual void onLayout(int x, int y, int width, int height)
	{
		View::onLayout(x, y, width, height);
		if (child)
			child->onLayout(x, y, width, height);
	}

	virtual void onMouseEvent(MouseEvent& event)
	{
		if (child && child->isInside(event.gx, event.gy))
		{
			MouseEvent childevent =
			{
				event.action,
				event.button,
				event.gx,
				event.gy,
				event.gx - child->getX(),
				event.gy - child->getY()
			};
			child->onMouseEvent(childevent);
		}
	}

	virtual void onKeyEvent(KeyEvent& event)
	{
		if (child)
			child->onKeyEvent(event);
	}

	ViewPtr getChild()
	{
		return child;
	}

	void setChild(ViewPtr newchild)
	{
		child = newchild;
	}

	virtual ~UnaryView() = default;
};

#endif /* INCLUDE_CORE_VIEW_UNARYVIEW_H_ */

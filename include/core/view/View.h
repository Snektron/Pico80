#ifndef INCLUDE_CORE_VIEW_VIEW_H_
#define INCLUDE_CORE_VIEW_VIEW_H_

#include <memory>
#include <nanovg.h>
#include "core/Event.h"

class View;

typedef std::shared_ptr<View> ViewPtr;

class View
{
protected:
	int x, y, w, h;
	bool focussed;

public:
	View();

	virtual void onUpdate(){};
	virtual void onRender(NVGcontext *vg){};
	virtual void onLayout(int x, int y, int w, int h);

	virtual void onMouseMoveEvent(MouseMoveEvent& event){};
	virtual bool onMouseButtonEvent(MouseButtonEvent& event){ return false; };
	virtual void onKeyEvent(KeyEvent& event){};
	virtual void onFocusEvent(bool focus){};

	int getLeft();
	int getTop();
	int getRight();
	int getBottom();
	int getWidth();
	int getHeight();
	bool contains(int x, int y);

	bool isFocussed();
	void setFocussed(bool focussed);

	virtual ~View() = default;
};

#endif /* INCLUDE_CORE_VIEW_VIEW_H_ */

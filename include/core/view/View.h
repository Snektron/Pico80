#ifndef INCLUDE_CORE_VIEW_VIEW_H_
#define INCLUDE_CORE_VIEW_VIEW_H_

#include <memory>
#include "core/Event.h"

class View
{
protected:
	int x, y, width, height;
	bool focussed;

public:
	View();

	virtual void onUpdate(){};
	virtual void onRender(){};
	virtual void onLayout(int x, int y, int width, int height);
	virtual void onMouseEvent(MouseEvent& event){};
	virtual void onKeyEvent(KeyEvent& event){};

	int getX();
	int getY();
	int getWidth();
	int getHeight();
	bool isFocussed();
	bool isInside(int x, int y);

	virtual ~View() = default;
};

typedef std::shared_ptr<View> ViewPtr;

#endif /* INCLUDE_CORE_VIEW_VIEW_H_ */

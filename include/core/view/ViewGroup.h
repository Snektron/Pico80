#ifndef INCLUDE_CORE_VIEW_VIEWGROUP_H_
#define INCLUDE_CORE_VIEW_VIEWGROUP_H_

#include "core/view/View.h"
#include <vector>

class ViewGroup : public View
{
protected:
	std::vector<ViewPtr> children;
	ViewPtr focus;

public:
	virtual void onUpdate();
	virtual void onRender(NVGcontext *vg);
	virtual void onLayout(int x, int y, int w, int h);
	virtual bool onMouseButtonEvent(MouseButtonEvent& event);
	virtual void onMouseMoveEvent(MouseMoveEvent& event);
	virtual void onKeyEvent(KeyEvent& event);
	virtual void onFocusEvent(bool focus);

	void addChild(ViewPtr child);
	void setChild(int index, ViewPtr child);
	void removeChild(ViewPtr child);
	void removeChild(int index);
	ViewPtr getChild(int index);
	int getChildCount();
	bool hasChildren();
	bool hasChild(ViewPtr child);
};

#endif /* INCLUDE_CORE_VIEW_VIEWGROUP_H_ */

#ifndef INCLUDE_CORE_VIEW_VIEWGROUP_H_
#define INCLUDE_CORE_VIEW_VIEWGROUP_H_

#include "core/view/View.h"
#include <vector>
#include "core/view/Layout.h"

class ViewGroup : public View
{
protected:
	std::vector<View::Ptr> children;
	Layout::Ptr layout;

public:
	virtual void onUpdate();
	virtual void onRender(NVGcontext *vg);
	virtual void onLayout(const Vector2i& pos, const Vector2i& size);
	virtual bool onMouseButtonEvent(MouseButtonEvent& event);
	virtual void onMouseMoveEvent(MouseMoveEvent& event);

	void setLayout(Layout::Ptr layout) { this->layout = layout; }
	Layout::Ptr getLayout() { return layout; }

	virtual Vector2i measure(Vector2i& parentSize);

	void addChild(View::Ptr child);
	void setChild(int index, View::Ptr child);
	void removeChild(View::Ptr child);
	void removeChild(int index);
	View::Ptr getChild(int index);
	int getChildCount();
	bool hasChildren();
	bool hasChild(View::Ptr child);

	typedef std::shared_ptr<ViewGroup> Ptr;
};

#endif /* INCLUDE_CORE_VIEW_VIEWGROUP_H_ */

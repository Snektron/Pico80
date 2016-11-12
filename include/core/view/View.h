#ifndef INCLUDE_CORE_VIEW_VIEW_H_
#define INCLUDE_CORE_VIEW_VIEW_H_

#include <memory>
#include <nanovg.h>
#include <Eigen/Core>
#include "core/Event.h"

using Eigen::Vector2i;

class View
{
protected:
	Vector2i preferredSize;
	Vector2i size;
	Vector2i pos;

public:
	View();

	virtual void onUpdate(){};
	virtual void onRender(NVGcontext *vg){};
	virtual void onLayout(const Vector2i& pos, const Vector2i& size);

	virtual void onMouseMoveEvent(MouseMoveEvent& event){};
	virtual bool onMouseButtonEvent(MouseButtonEvent& event){ return false; };
	virtual void onKeyEvent(KeyEvent& event){};
	virtual void onFocusEvent(bool focus){};

	virtual Vector2i measure(Vector2i& parentSize) { return preferredSize; }

	Vector2i getPreferredSize() { return preferredSize; }
	void setPreferredSize(Vector2i& v) { preferredSize = v; }
	Vector2i getSize() { return size; }
	void setSize(Vector2i& v) { size = v; }
	Vector2i getPos() { return pos; }
	void setPos(Vector2i& v) { pos = v; }

	int getLeft();
	int getTop();
	int getRight();
	int getBottom();
	int getWidth();
	int getHeight();
	bool contains(int x, int y);
	bool contains(Vector2i& coord);

	virtual ~View() = default;

	typedef std::shared_ptr<View> Ptr;
};

#endif /* INCLUDE_CORE_VIEW_VIEW_H_ */

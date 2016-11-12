#include "core/view/ViewGroup.h"
#include <algorithm>

void ViewGroup::onUpdate()
{
	View::onUpdate();
	for (auto child : children)
		child->onUpdate();
}

void ViewGroup::onRender(NVGcontext *vg)
{
	View::onRender(vg);

	if (!hasChildren())
		return;

	nvgSave(vg);
	nvgTranslate(vg, getLeft(), getTop());

	for (auto child : children)
	{
		nvgSave(vg);
	//	nvgScissor(vg, child->getLeft(), child->getTop(), child->getWidth(), child->getHeight());
		child->onRender(vg);
		nvgRestore(vg);
	}

	nvgRestore(vg);
}

void ViewGroup::onLayout(const Vector2i& pos, const Vector2i& size)
{
	View::onLayout(pos, size);

	if (layout)
		layout->onLayout(pos, size, this);
	else
		for (auto child : children)
			child->onLayout(Vector2i::Zero(), size);
}

bool ViewGroup::onMouseButtonEvent(MouseButtonEvent& event)
{
	for (auto child : children)
	{
		MouseButtonEvent childEvent =
		{
			event.action,
			event.button,
			event.gx,
			event.gy,
			event.x - getLeft(),
			event.y - getTop()
		};

		if (child->contains(childEvent.x, childEvent.y))
			child->onMouseButtonEvent(childEvent);
	}

	return false;
}

void ViewGroup::onMouseMoveEvent(MouseMoveEvent& event)
{
	View::onMouseMoveEvent(event);

	for (auto child : children)
	{
		MouseMoveEvent childEvent =
		{
			event.action,
			event.gx,
			event.gy,
			event.x - getLeft(),
			event.y - getTop()
		};

		if (child->contains(childEvent.x, childEvent.y))
			child->onMouseMoveEvent(childEvent);
	}
}

Vector2i ViewGroup::measure(Vector2i& parentSize)
{
	if (layout)
		return layout->measure(parentSize, this);
	return Vector2i(MATCH_PARENT, MATCH_PARENT);
}

void ViewGroup::addChild(View::Ptr child)
{
	if (child)
		children.push_back(child);
}

void ViewGroup::setChild(int index, View::Ptr child)
{
	if (index < getChildCount() && child)
		children[index] = child;
}

void ViewGroup::removeChild(View::Ptr child)
{
	if (child)
		children.erase(std::remove(children.begin(), children.end(), child));
}

void ViewGroup::removeChild(int index)
{
	children.erase(children.begin() + index);
}

View::Ptr ViewGroup::getChild(int index)
{
	return children[index];
}

int ViewGroup::getChildCount()
{
	return children.size();
}

bool ViewGroup::hasChildren()
{
	return !children.empty();
}

bool ViewGroup::hasChild(View::Ptr child)
{
	return std::find(children.begin(), children.end(), child) != children.end();
}

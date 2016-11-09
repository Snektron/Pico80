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

void ViewGroup::onLayout(int x, int y, int w, int h)
{
	View::onLayout(x, y, w, h);
	for (auto child : children)
		child->onLayout(0, 0, w, h);
}

bool ViewGroup::onMouseButtonEvent(MouseButtonEvent& event)
{
	ViewPtr toFocus(nullptr);

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

		if (child->contains(childEvent.x, childEvent.y) &&
			child->onMouseButtonEvent(childEvent))
			focus = child;
	}

	bool focusChanged = toFocus != focus;

	if (focus && focus->isFocussed())
		focus->onFocusEvent(false);

	focus = toFocus;

	if (focus && !focus->isFocussed())
		toFocus->onFocusEvent(true);

	return focusChanged;
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

		if (child->isFocussed() && child->contains(childEvent.x, childEvent.y))
			child->onMouseMoveEvent(childEvent);
	}
}

void ViewGroup::onKeyEvent(KeyEvent& event)
{
	View::onKeyEvent(event);

	for (auto child : children)
	{
		if (child->isFocussed())
			child->onKeyEvent(event);
	}
}

void ViewGroup::onFocusEvent(bool focus)
{
	View::setFocussed(focus);

	if (focus)
		return;

	for (auto child : children)
	{
		if (child->isFocussed())
			child->onFocusEvent(false);
	}
}

void ViewGroup::addChild(ViewPtr child)
{
	if (child)
		children.push_back(child);
}

void ViewGroup::setChild(int index, ViewPtr child)
{
	if (index < getChildCount() && child)
		children[index] = child;
}

void ViewGroup::removeChild(ViewPtr child)
{
	if (child)
		children.erase(std::remove(children.begin(), children.end(), child));
}

void ViewGroup::removeChild(int index)
{
	children.erase(children.begin() + index);
}

ViewPtr ViewGroup::getChild(int index)
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

bool ViewGroup::hasChild(ViewPtr child)
{
	return std::find(children.begin(), children.end(), child) != children.end();
}

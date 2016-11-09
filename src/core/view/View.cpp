#include "core/view/View.h"

View::View():
	x(0), y(0),
	w(0), h(0),
	focussed(false)
{}

void View::onLayout(int x, int y, int w, int h)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

int View::getLeft()
{
	return x;
}

int View::getTop()
{
	return y;
}

int View::getRight()
{
	return x + w;
}

int View::getBottom()
{
	return y + h;
}

int View::getWidth()
{
	return w;
}

int View::getHeight()
{
	return h;
}

bool View::contains(int x, int y)
{
	return x >= getLeft() && y >= getTop() && x < getRight() && y < getBottom();
}

bool View::isFocussed()
{
	return focussed;
}

void View::setFocussed(bool focussed)
{
	this->focussed = focussed;
}

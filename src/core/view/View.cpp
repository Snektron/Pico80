#include "core/view/View.h"

View::View():
	x(0), y(0),
	width(0), height(0),
	focussed(false)
{}

void View::onLayout(int x, int y, int width, int height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

int View::getX()
{
	return x;
}

int View::getY()
{
	return y;
}

int View::getWidth()
{
	return width;
}

int View::getHeight()
{
	return height;
}

bool View::isFocussed()
{
	return focussed;
}

bool View::isInside(int x, int y)
{
	return x >= getX() && y >= getY() && x < getX() + getWidth() && y < getY() + getHeight();
}

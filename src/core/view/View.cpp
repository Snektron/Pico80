#include "core/view/View.h"

View::View():
	View(100, -1)
{}

View::View(float far, float near):
	f(far), n(near),
	x(0), y(0),
	width(0), height(0)
{}

void View::update()
{
	onUpdate();
}

void View::render()
{
	onRender();
}

void View::resize(int x, int y, int width, int height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;

	onResize(width, height);
}

float View::getWidth()
{
	return width;
}

float View::getHeight()
{
	return height;
}

#include "core/view/View.h"
#include <eigen3/Eigen/Core>
#include "core/gl/Util.h"

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
	onRender(matrix);
}

void View::resize(float x, float y, float width, float height)
{
	this->width = width;
	this->height = height;

	Util::ortho(matrix, x, x + width, y, y + height, 2, -1);

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

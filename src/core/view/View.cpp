#include "core/view/View.h"
#include <eigen3/Eigen/Core>
#include "core/Graphics.h"
#include "core/Logger.h"

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

void View::render(Eigen::Matrix4f& mv, Eigen::Matrix4f& p)
{
	Eigen::Matrix4f mv2 = mv;
	mv2(0, 3) += x;
	mv2(1, 3) += y;
	onRender(mv2, p);
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

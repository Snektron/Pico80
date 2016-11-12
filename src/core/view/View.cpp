#include "core/view/View.h"
View::View():
	preferredSize(Vector2i::Zero()),
	size(Vector2i::Zero()),
	pos(Vector2i::Zero())
{}

void View::onLayout(const Vector2i& pos, const Vector2i& size)
{
	this->pos = pos;
	this->size = size;
}

int View::getLeft()
{
	return pos.x();
}

int View::getTop()
{
	return pos.y();
}

int View::getRight()
{
	return pos.x() + size.x();
}

int View::getBottom()
{
	return pos.y() + size.y();
}

int View::getWidth()
{
	return size.x();
}

int View::getHeight()
{
	return size.y();
}

bool View::contains(int x, int y)
{
	return x >= getLeft() && y >= getTop() && x < getRight() && y < getBottom();
}

bool View::contains(Vector2i& coord)
{
	return contains(coord.x(), coord.y());
}

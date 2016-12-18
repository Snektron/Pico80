#include "gui/display/Display.h"
#include <cstdint>
#include "gui/display/DisplayRenderer.h"

Display::Display():
	dirty(false)
{
	setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton);
	setAcceptHoverEvents(true);
}

QQuickFramebufferObject::Renderer* Display::createRenderer() const
{
	return new DisplayRenderer();
}

bool Display::isDirty()
{
	bool displayDirty = dirty;
	dirty = false;
	return displayDirty;
}

Instance* Display::getInstance()
{
	return instance;
}

void Display::instanceChanged(Instance *instance)
{
	this->instance = instance;
	invalidate();
}

void Display::invalidate()
{
	dirty = true;
	update();
}

void Display::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_F12)
		emit onTurnedOn();
}

void Display::keyReleaseEvent(QKeyEvent *event)
{

}

void Display::mousePressEvent(QMouseEvent *event)
{
	setFocus(true);
}

void Display::mouseReleaseEvent(QMouseEvent *event)
{
}

void Display::mouseMoveEvent(QMouseEvent *event)
{
}

void Display::hoverMoveEvent(QHoverEvent *event)
{
}

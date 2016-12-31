#include "gui/display/Display.h"
#include "gui/display/DisplayRenderer.h"

Display::Display()
{
	setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton);
	setAcceptHoverEvents(true);
}

QQuickFramebufferObject::Renderer* Display::createRenderer() const
{
	return new DisplayRenderer();
}


void Display::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_F12)
		emit onTurnedOn();
	emit onKeyPress(event);
}

void Display::keyReleaseEvent(QKeyEvent *event)
{
	emit onKeyRelease(event);
}

void Display::mousePressEvent(QMouseEvent *event)
{
	setFocus(true);
	emit onMousePress(event);
}

void Display::mouseReleaseEvent(QMouseEvent *event)
{
	emit onMouseRelease(event);
}

void Display::mouseMoveEvent(QMouseEvent *event)
{
	emit onMouseMove(event);
}

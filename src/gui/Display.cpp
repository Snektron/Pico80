#include "gui/Display.h"
#include "gui/DisplayRenderer.h"
#include "core/Logger.h"
#include "core/Keys.h"

Display::Display():
	vram(nullptr)
{
	setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton);
}

QQuickFramebufferObject::Renderer* Display::createRenderer() const
{
	return new DisplayRenderer();
}

Vram* Display::getVram()
{
	return this->vram;
}

bool Display::isDirty()
{
	bool displayDirty = dirty;
	dirty = false;
	return displayDirty;
}

void Display::invalidate(Vram *vram)
{
	dirty = true;
	this->vram = vram;
	update();
}

void Display::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_F12)
		emit turnedOn();
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

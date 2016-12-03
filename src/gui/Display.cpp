#include "gui/Display.h"
#include <cstdint>
#include "gui/DisplayRenderer.h"
#include "core/Logger.h"
#include "emu/pico80/Keys.h"
#include "emu/pico80/Platform.h"

Display::Display():
	vram(nullptr)
{
	setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton);
	setAcceptHoverEvents(true);
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

int clamp(int x, int a, int b)
{
	return x < a ? a : x > b ? b : x;
}

void Display::moveEvent(int ex, int ey)
{
	uint8_t x = (uint8_t) clamp(ex * 128 / width(), 0, 128);
	uint8_t y = (uint8_t) clamp(ey * 128 / width(), 0, 128);
	emit mouseMove(x, y);
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
	uint8_t key = mapQTKey((Qt::Key) event->key(), event->modifiers());
	if (key != K_NONE)
	{
		emit keyPress(key);
		event->accept();
	}
}

void Display::keyReleaseEvent(QKeyEvent *event)
{
	uint8_t key = mapQTKey((Qt::Key)event->key(), event->modifiers());
	if (key != K_NONE)
	{
		emit keyRelease(key);
		event->accept();
	}
}

void Display::mousePressEvent(QMouseEvent *event)
{
	setFocus(true);
	if (event->button() == Qt::LeftButton)
		emit mousePress(MOUSE_BTN_LEFT);
	else if (event->button() == Qt::RightButton)
		emit mousePress(MOUSE_BTN_RIGHT);
	event->accept();
}

void Display::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
		emit mouseRelease(MOUSE_BTN_LEFT);
	else if (event->button() == Qt::RightButton)
		emit mouseRelease(MOUSE_BTN_RIGHT);
	event->accept();
}

void Display::mouseMoveEvent(QMouseEvent *event)
{
	moveEvent(event->x(), event->y());
	event->accept();
}

void Display::hoverMoveEvent(QHoverEvent *event)
{
	moveEvent(event->pos().x(), event->pos().y());
	event->accept();
}

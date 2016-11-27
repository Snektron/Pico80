#include "gui/Display.h"
#include "gui/DisplayRenderer.h"

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

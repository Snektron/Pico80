#ifndef DISPLAYRENDERER_H
#define DISPLAYRENDERER_H

#include <QSize>
#include <QOpenGLFramebufferObject>
#include <QQuickFramebufferObject>
#include <picore/api/IDisplay.h>
#include "gui/display/Display.h"

class DisplayRenderer: public QQuickFramebufferObject::Renderer
{
private:
	Display *parent;
	IDisplay *display;

public:
	DisplayRenderer();
	QOpenGLFramebufferObject* createFramebufferObject(const QSize &size);
	void synchronize(QQuickFramebufferObject *item);
	void render();
	~DisplayRenderer();
};

#endif // DISPLAYRENDERER_H
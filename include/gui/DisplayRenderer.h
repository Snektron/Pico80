#ifndef DISPLAYRENDERER_H
#define DISPLAYRENDERER_H

#include <QSize>
#include <QOpenGLFunctions>
#include <QOpenGLFramebufferObject>
#include <QQuickFramebufferObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include "gui/Display.h"

class DisplayRenderer : public QQuickFramebufferObject::Renderer, public QOpenGLFunctions
{
private:
	QSize viewport;
	Display *display;
	QOpenGLShaderProgram *shader;
	QOpenGLTexture *texture;
	QOpenGLTexture *palette;

public:
	DisplayRenderer();
	QOpenGLFramebufferObject* createFramebufferObject(const QSize &size);
	void synchronize(QQuickFramebufferObject *item);
	void render();
	void initialize();
	void updateTexture();
	~DisplayRenderer();
};

#endif // DISPLAYRENDERER_H

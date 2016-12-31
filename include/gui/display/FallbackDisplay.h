#ifndef FALLBACKRENDERER_H
#define FALLBACKRENDERER_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <picore/api/IDisplay.h>

class FallbackDisplayRenderer: public IDisplay, public QOpenGLFunctions
{
private:
	QOpenGLShaderProgram *shader;
	QOpenGLTexture *texture;

public:
	FallbackDisplayRenderer();
	void render();
	~FallbackDisplayRenderer();
};

#endif // FALLBACKRENDERER_H

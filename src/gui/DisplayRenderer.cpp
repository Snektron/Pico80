#include "gui/DisplayRenderer.h"
#include <cstdint>
#include <cstring>
#include <QQuickWindow>
#include "gui/Display.h"
#include "core/Logger.h"
#include "emu/Platform.h"
#include "emu/device/Screen.h"

const float vertices[] =
{
	-1, -1,
	 1, -1,
	-1,  1,
	 1,  1
};

const float texcoords[] =
{
	0, 0,
	1, 0,
	0, 1,
	1, 1
};


DisplayRenderer::DisplayRenderer():
	shader(nullptr),
	display(nullptr)
{}

QOpenGLFramebufferObject* DisplayRenderer::createFramebufferObject(const QSize &size)
{
	QOpenGLFramebufferObjectFormat format;
	format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
	return new QOpenGLFramebufferObject(size, format);
}

void DisplayRenderer::synchronize(QQuickFramebufferObject *item)
{
	this->display = (Display*) item;
}

void DisplayRenderer::render()
{
	if (!shader)
		initialize();
	else
		shader->bind();

	if (display && display->isDirty())
		updateTexture();

	shader->enableAttributeArray(0);
	shader->setAttributeArray(0, GL_FLOAT, vertices, 2);
	shader->enableAttributeArray(1);
	shader->setAttributeArray(1, GL_FLOAT, texcoords, 2);

	texture->bind(0);
	palette->bind(1);

	glDisable(GL_DEPTH_TEST);

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	shader->disableAttributeArray(1);
	shader->disableAttributeArray(0);
	shader->release();

	if (display)
		display->window()->resetOpenGLState();
}

void DisplayRenderer::initialize()
{
	initializeOpenGLFunctions();
	shader = new QOpenGLShaderProgram();
	shader->addShaderFromSourceFile(QOpenGLShader::Vertex, QStringLiteral(":/shader/Display.vsh"));
	shader->addShaderFromSourceFile(QOpenGLShader::Fragment, QStringLiteral(":/shader/Display.fsh"));
	shader->bindAttributeLocation("aVertices", 0);
	shader->bindAttributeLocation("aTexCoords", 1);
	shader->link();

	texture = new QOpenGLTexture(QOpenGLTexture::Target2D);
	texture->setMinificationFilter(QOpenGLTexture::Nearest);
	texture->setMagnificationFilter(QOpenGLTexture::Nearest);
	texture->setSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	texture->setFormat(QOpenGLTexture::RGBA8_UNorm);
	texture->allocateStorage(QOpenGLTexture::RGBA, QOpenGLTexture::UInt32);

	palette = new QOpenGLTexture(QImage(":/textures/palette.png").mirrored());
	palette->setMinificationFilter(QOpenGLTexture::Nearest);
	palette->setMagnificationFilter(QOpenGLTexture::Nearest);

	shader->bind();
	shader->setUniformValue("uTexture", 0);
	shader->setUniformValue("uPalette", 1);
}

void DisplayRenderer::updateTexture()
{
	if (!display->getVram())
		return;

	uint8_t *data = display->getVram()->rawData();

	if (!data)
		return;
	texture->setData(QOpenGLTexture::Red, QOpenGLTexture::UInt8, data);
}

DisplayRenderer::~DisplayRenderer()
{
	if (shader)
		delete shader;
	if (texture)
		delete texture;
	if (palette)
		delete palette;
}

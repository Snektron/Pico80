#include "gui/DisplayRenderer.h"
#include <cstdint>
#include <QQuickWindow>
#include "gui/Display.h"
#include "core/Logger.h"
#include "emu/Platform.h"
#include "emu/device/Screen.h"

#define COLOR(r, g, b) {r, g, b, 0xFF}

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

const color_t palette[16] =
{
	COLOR( 20,  12,  28), // 0 black
	COLOR( 68,  36,  52), // 1 plum
	COLOR( 48,  52, 109), // 2 midnight
	COLOR( 78,  74,  78), // 3 iron
	COLOR(133,  76,  48), // 4 earth
	COLOR( 52, 101,  36), // 5 moss
	COLOR(208,  70,  72), // 6 berry
	COLOR(117, 113,  97), // 7 olive
	COLOR( 89, 125, 206), // 8 cornflower
	COLOR(210, 125,  44), // 9 ocher
	COLOR(133, 149, 161), // A slate
	COLOR(109, 170,  44), // B leaf
	COLOR(210, 170, 153), // C peach
	COLOR(109, 194, 202), // D sky
	COLOR(218, 212,  94), // E maize
	COLOR(222, 238, 214)  // F peppermint
};

DisplayRenderer::DisplayRenderer():
	shader(nullptr),
	display(nullptr)
{}

QOpenGLFramebufferObject* DisplayRenderer::createFramebufferObject(const QSize &size)
{
	viewport = size;
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

	float aspect = (float) viewport.width() / (float) viewport.height();
	QVector2D scale(1, 1);

	if (aspect > 1.f)
		scale.setX(1.f/aspect);
	else
		scale.setY(aspect);

	shader->enableAttributeArray(0);
	shader->setAttributeArray(0, GL_FLOAT, vertices, 2);
	shader->enableAttributeArray(1);
	shader->setAttributeArray(1, GL_FLOAT, texcoords, 2);
	shader->setUniformValue("uScale", scale);
	texture->bind(0);

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

	shader->bind();
	shader->setUniformValue("uTexture", 0);
}

void DisplayRenderer::updateTexture()
{
	color_t pixels[SCREEN_WIDTH * SCREEN_HEIGHT];
	uint8_t *data = display->getVram()->rawData();
	for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++)
		pixels[i] = palette[data[i] & 0xF];
	texture->setData(QOpenGLTexture::RGBA, QOpenGLTexture::UInt8, pixels);
}

DisplayRenderer::~DisplayRenderer()
{
	if (shader)
		delete shader;
	if (texture)
		delete texture;
}

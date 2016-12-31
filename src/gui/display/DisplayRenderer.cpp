#include "gui/display/DisplayRenderer.h"
#include <QQuickWindow>
#include "gui/display/Display.h"
#include "gui/display/FallbackDisplay.h"

DisplayRenderer::DisplayRenderer():
	parent(nullptr),
	display(nullptr)
{}

QOpenGLFramebufferObject* DisplayRenderer::createFramebufferObject(const QSize &size)
{
	QOpenGLFramebufferObjectFormat format;
	return new QOpenGLFramebufferObject(size, format);
}

void DisplayRenderer::synchronize(QQuickFramebufferObject *item)
{
	this->parent = (Display*) item;

/*	if (parent && parent->isDirty())
	{
		if (display)
		{
			delete display;
			display = nullptr;
		}

	//	if (parent->getInstance())
	//		display = parent->getInstance()->getPlugin()->createDisplay();
	} */

	if (!display)
	{
		qWarning() << "Failed to instantiate display";
		display = new FallbackDisplayRenderer();
	}
}

void DisplayRenderer::render()
{
	if (display)
		display->render();
	if (parent)
		parent->window()->resetOpenGLState();
}

DisplayRenderer::~DisplayRenderer()
{
	if (display)
		delete display;
}

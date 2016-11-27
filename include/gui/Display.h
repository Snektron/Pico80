#ifndef DISPLAY_H
#define DISPLAY_H

#include <QQuickFramebufferObject>
#include "emu/device/Screen.h"

class Display : public QQuickFramebufferObject
{
	Q_OBJECT
private:
	Vram *vram;
	bool dirty;

public:
	QQuickFramebufferObject::Renderer* createRenderer() const;
	Vram* getVram();
	bool isDirty();

public slots:
	void invalidate(Vram *vram);
};

#endif // DISPLAY_H

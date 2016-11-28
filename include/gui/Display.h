#ifndef DISPLAY_H
#define DISPLAY_H

#include <QQuickFramebufferObject>
#include <QKeyEvent>
#include "emu/device/Screen.h"

class Display : public QQuickFramebufferObject
{
	Q_OBJECT
private:
	Vram *vram;
	bool dirty;

public:
	Display();
	QQuickFramebufferObject::Renderer* createRenderer() const;
	Vram* getVram();
	bool isDirty();

public slots:
	void invalidate(Vram *vram);
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

signals:
	void keyPress(uint8_t key);
	void keyRelease(uint8_t key);
	void turnedOn();
};

#endif // DISPLAY_H

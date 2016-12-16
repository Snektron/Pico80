#ifndef DISPLAY_H
#define DISPLAY_H

#include <QQuickFramebufferObject>
#include "emu/pico80/device/Screen.h"

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

	void moveEvent(int x, int y);

public slots:
	void invalidate(Vram *vram);
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void hoverMoveEvent(QHoverEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

signals:
	void turnedOn();
	void keyPress(uint8_t key);
	void keyRelease(uint8_t key);
	void mousePress(uint8_t button);
	void mouseRelease(uint8_t button);
	void mouseMove(uint8_t x, uint8_t y);
};

#endif // DISPLAY_H

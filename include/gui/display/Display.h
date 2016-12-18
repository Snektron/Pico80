#ifndef DISPLAY_H
#define DISPLAY_H

#include <QQuickFramebufferObject>
#include "core/Instance.h"

class Display : public QQuickFramebufferObject
{
	Q_OBJECT
private:
	Instance *instance;
	bool dirty;

public:
	Display();
	QQuickFramebufferObject::Renderer* createRenderer() const;
	bool isDirty();
	Instance* getInstance();

public slots:
	void instanceChanged(Instance *instance);
	void invalidate();
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void hoverMoveEvent(QHoverEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

signals:
	void onTurnedOn();
	void onKeyPress(QKeyEvent *event);
	void onKeyRelease(QKeyEvent *event);
	void onMousePress(QMouseEvent *event);
	void onMouseRelease(QMouseEvent *event);
	void onMouseMove(QMouseEvent *event);
};

#endif // DISPLAY_H

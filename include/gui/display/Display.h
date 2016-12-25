#ifndef DISPLAY_H
#define DISPLAY_H

#include <QQuickFramebufferObject>
#include "api/IPlugin.h"

class Display : public QQuickFramebufferObject
{
	Q_OBJECT
private:
	bool dirty;

public:
	Display();
	QQuickFramebufferObject::Renderer* createRenderer() const;
	bool isDirty();

public slots:
	void pluginChanged(IPlugin *plugin);
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

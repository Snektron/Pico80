#ifndef DISPLAY_H
#define DISPLAY_H

#include <QQuickFramebufferObject>
#include <picore/PluginEngine.h>

class Display : public QQuickFramebufferObject
{
	Q_OBJECT
private:

public:
	Display();
	QQuickFramebufferObject::Renderer* createRenderer() const;

public slots:
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

signals:
	void onPluginChanged(PluginEngine *engine);
	void onTurnedOn();
	void onKeyPress(QKeyEvent *event);
	void onKeyRelease(QKeyEvent *event);
	void onMousePress(QMouseEvent *event);
	void onMouseRelease(QMouseEvent *event);
	void onMouseMove(QMouseEvent *event);	
};

#endif // DISPLAY_H

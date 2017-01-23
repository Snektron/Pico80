#ifndef PICOQMLENGINE_H
#define PICOQMLENGINE_H

#include <QQuickItem>
#include <QString>
#include "Pico80/api/IPicoQmlEngine.h"
#include "core/theme/Theme.h"

class PicoQmlEngine: public IPicoQmlEngine
{
	Q_OBJECT
public:
	PicoQmlEngine();
	QQuickItem* loadComponent(QUrl file);
	void setDisplay(QQuickItem *display);
	void addSidebarView(QQuickItem *item, QString id);
};

#endif // PICOQMLENGINE_H

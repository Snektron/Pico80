#ifndef PICOQMLENGINE_H
#define PICOQMLENGINE_H

#include <QQuickItem>
#include "Pico80/api/IPicoQmlEngine.h"

class PicoQmlEngine: public IPicoQmlEngine
{
public:
	QQuickItem* setDisplay(QUrl file);
	void setDisplay(QQuickItem *display);
};

#endif // PICOQMLENGINE_H

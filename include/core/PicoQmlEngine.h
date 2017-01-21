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
	QQuickItem* setDisplay(QUrl file);
	void setDisplay(QQuickItem *display);
};

#endif // PICOQMLENGINE_H

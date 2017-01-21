#ifndef IPICOENGINE_H
#define IPICOENGINE_H

#include <QQmlContext>
#include "Pico80/api/IPicoSettings.h"
#include "Pico80/api/IPicoQmlEngine.h"
#include "Pico80/api/ITheme.h"

class IPicoEngine
{
public:
	virtual IPicoSettings* settings() = 0;
	virtual ITheme* theme() = 0;
	virtual IPicoQmlEngine* qmlEngine() = 0;
	virtual QQmlContext* rootContext() = 0;
	virtual ~IPicoEngine() = default;
};

#endif // IPICOENGINE_H

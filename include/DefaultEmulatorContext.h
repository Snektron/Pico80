#ifndef DEFAULTEMULATORCONTEXT_H
#define DEFAULTEMULATORCONTEXT_H

#include "Pico80/api/IEmulatorContext.h"
#include "Pico80/api/IPicoEngine.h"

class DefaultEmulatorContext: public IEmulatorContext
{
private:
	QQuickItem *display;

public:
	DefaultEmulatorContext(IPicoEngine *engine);
	~DefaultEmulatorContext();
};

#endif // DEFAULTEMULATORCONTEXT_H

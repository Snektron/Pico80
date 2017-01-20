#ifndef DEFAULTEMULATORCONTEXT_H
#define DEFAULTEMULATORCONTEXT_H

#include "Pico80/api/IEmulatorContext.h"

class DefaultEmulatorContext: public IEmulatorContext
{
private:
	QQuickItem *display;

public:
	DefaultEmulatorContext(IPicoQmlEngine *engine);
	~DefaultEmulatorContext();
};

#endif // DEFAULTEMULATORCONTEXT_H

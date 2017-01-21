#ifndef PLUGIN_H
#define PLUGIN_H

#include <QString>
#include "Pico80/api/IEmulatorContext.h"
#include "Pico80/api/IPicoEngine.h"

class IPlugin
{
public:
	virtual QString name() = 0;
	virtual IEmulatorContext* createContext(IPicoEngine *engine) = 0;
	virtual ~IPlugin() = default;
};

#define IPlugin_iid "space.quantuminfinity.pico80.IPlugin"
Q_DECLARE_INTERFACE(IPlugin, IPlugin_iid)

#endif // PLUGIN_H

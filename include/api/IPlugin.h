#ifndef PLUGIN_H
#define PLUGIN_H

#include <QString>
#include "api/IDisplay.h"
#include "api/IEmulator.h"
#include "api/PluginEngine.h"

class IPlugin
{
public:
	virtual QString name() = 0;
	virtual void registerPlugin(PluginEngine *engine) = 0;
	virtual IEmulator* createEmulator() = 0;
	virtual IDisplay* createDisplay() = 0;
	virtual ~IPlugin() = default;
};

#define IPlugin_iid "space.quantuminfinity.pico80.IPlugin"
Q_DECLARE_INTERFACE(IPlugin, IPlugin_iid)

#endif // PLUGIN_H

#ifndef PLUGIN_H
#define PLUGIN_H

#include "api/IEmulator.h"

#define IPlugin_iid "space.quantuminfinity.pico80.IPlugin"

class IPlugin
{
public:
	IEmulator* createEmulator();
	void destroyEmulator(IEmulator* emulator);

	virtual ~IPlugin() = default;
};

Q_DECLARE_INTERFACE(IPlugin, IPlugin_iid)

#endif // PLUGIN_H

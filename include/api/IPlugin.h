#ifndef PLUGIN_H
#define PLUGIN_H

#include <QString>
#include "api/IDisplay.h"
#include "api/IEmulator.h"

class IPlugin
{
public:
	QString name();

	IEmulator* createEmulator();
	void destroyEmulator(IEmulator *emulator);

	IDisplay* createDisplay();
	void destroyDisplay(IDisplay *display);

	virtual ~IPlugin() = default;
};

#define IPlugin_iid "space.quantuminfinity.pico80.IPlugin"
Q_DECLARE_INTERFACE(IPlugin, IPlugin_iid)

#endif // PLUGIN_H

#ifndef PLUGINENGINE_H
#define PLUGINENGINE_H

#include <QObject>
#include <QScopedPointer>
#include "api/Factory.h"
#include "api/IDisplay.h"
#include "api/IEmulator.h"

typedef Factory<IDisplay> DisplayFactory;
typedef Factory<IEmulator> EmulatorFactory;

class PluginEngine: public QObject
{
	Q_OBJECT
private:
	DisplayFactory displayFactory;
	EmulatorFactory emulatorFactory;

public:
	PluginEngine();
	~PluginEngine();

	template<typename T>
	void registerDisplay();
	void registerDisplayFactory(DisplayFactory *factory);
};

#endif // PLUGINENGINE_H

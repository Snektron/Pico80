#ifndef INSTANCE_H
#define INSTANCE_H

#include <QObject>
#include "api/IDisplay.h"
#include "api/IEmulator.h"
#include "api/IPlugin.h"

class Instance: public QObject
{
	Q_OBJECT
private:
	IPlugin *plugin;

public:
	Instance(IPlugin *plugin);
	IPlugin* getPlugin();
	~Instance();
};

#endif // INSTANCE_H

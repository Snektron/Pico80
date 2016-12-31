#ifndef DISPLAYWRAPPER_H
#define DISPLAYWRAPPER_H

#include <QObject>
#include <picore/PluginEngine.h>

class DisplayWrapper: public QObject
{
	Q_OBJECT
public:
	DisplayWrapper();
	~DisplayWrapper();

public slots:
	void pluginChanged(PluginEngine *engine);
};

#endif // DISPLAYWRAPPER_H

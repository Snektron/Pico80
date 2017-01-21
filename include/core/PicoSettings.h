#ifndef PICOSETTINGS_H
#define PICOSETTINGS_H

#include <QObject>
#include <QVariantMap>
#include "Pico80/api/IPicoSettings.h"

class PicoSettings: public QObject, public IPicoSettings
{
	Q_OBJECT
private:
	QVariantMap settings;

public:
	PicoSettings();
	~PicoSettings();
	Q_INVOKABLE void load();
	Q_INVOKABLE void save();
	Q_INVOKABLE QVariant value(QString key, QVariant defaultValue = QVariant());
	Q_INVOKABLE void setValue(QString key, QVariant value);
};

#endif // PICOSETTINGS_H

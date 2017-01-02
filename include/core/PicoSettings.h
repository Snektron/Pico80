#ifndef PICOSETTINGS_H
#define PICOSETTINGS_H

#include <QObject>
#include <QVariantMap>

class PicoSettings: public QObject
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

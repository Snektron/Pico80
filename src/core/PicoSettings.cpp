#include "core/PicoSettings.h"
#include <QSettings>
#include <QDebug>

PicoSettings::PicoSettings()
{
	load();
}

PicoSettings::~PicoSettings()
{
	save();
}

void PicoSettings::load()
{
	QSettings qsettings("settings.ini", QSettings::IniFormat);

	foreach (QString key, qsettings.allKeys())
		settings[key] = qsettings.value(key);
}

void PicoSettings::save()
{
	QSettings qsettings("settings.ini", QSettings::IniFormat);

	QMapIterator<QString, QVariant> i(settings);
	while (i.hasNext())
	{
		i.next();
		qsettings.setValue(i.key(), i.value());
	}
}

QVariant PicoSettings::value(QString key, QVariant defaultValue)
{
	if (!settings[key].isNull())
		return settings[key];
	settings[key] = defaultValue;
	return defaultValue;
}

void PicoSettings::setValue(QString key, QVariant value)
{
	settings[key] = value;
}

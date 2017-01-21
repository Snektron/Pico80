#ifndef IPICOSETTINGS_H
#define IPICOSETTINGS_H

#include <QVariant>

class IPicoSettings
{
public:
	virtual QVariant value(QString key, QVariant defaultValue = QVariant()) = 0;
	virtual void setValue(QString key, QVariant value) = 0;
	virtual ~IPicoSettings() = default;
};

#endif // IPICOSETTINGS_H

#ifndef THEME_H
#define THEME_H

#include <QObject>
#include <QVariant>
#include "Pico80/api/ITheme.h"
#include "core/theme/Node.h"

class Theme: public QObject, public ITheme
{
	Q_OBJECT
private:
	MapNode *root;

public:
	Theme();
	~Theme();
	void addFile(QString filename);
	QVariant toVariant();

signals:
	themeChanged();
};

#endif // THEME_H

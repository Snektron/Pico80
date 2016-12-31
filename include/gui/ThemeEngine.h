#ifndef THEME_H
#define THEME_H

#include <QObject>
#include <QVariant>

class ThemeEngine: public QObject
{
	Q_OBJECT
private:

public:
	QVariant loadDefaultTheme();
	QVariant loadTheme();
};

#endif // THEME_H

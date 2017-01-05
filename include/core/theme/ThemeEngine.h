#ifndef THEME_H
#define THEME_H

#include <QObject>
#include <QVariant>

class ThemeEngine: public QObject
{
	Q_OBJECT
private:
	QVariant theme;

public:
	ThemeEngine();
	QVariant loadDefaultTheme();
	QVariant loadTheme();
	QVariant getTheme();

signals:
	themeChanged();
};

#endif // THEME_H

#include "gui/ThemeEngine.h"
#include <QVariantMap>

ThemeEngine::ThemeEngine()
{
	theme = QVariant();
}

QVariant ThemeEngine::loadDefaultTheme()
{
	return QVariant();
}

QVariant ThemeEngine::loadTheme()
{
	theme = loadDefaultTheme();
	emit themeChanged();
	return theme;
}

QVariant ThemeEngine::getTheme()
{
	return theme;
}

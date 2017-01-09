#include "core/theme/ThemeEngine.h"
#include <QVariantMap>
#include <core/theme/ThemeParser.h>

ThemeEngine::ThemeEngine()
{
	theme = QVariant();
}

QVariant ThemeEngine::loadDefaultTheme()
{
	ThemeParser parser(":/theme/test.thm");
//	ThemeParser parser("test.txt");
	theme = parser.parse();
	return theme;
}

QVariant ThemeEngine::loadTheme()
{
	loadDefaultTheme();
	emit themeChanged();
	return theme;
}

QVariant ThemeEngine::getTheme()
{
	return theme;
}

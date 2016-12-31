#include "gui/ThemeEngine.h"
#include <QVariantMap>

QVariant ThemeEngine::loadDefaultTheme()
{
	return QVariant();
}

QVariant ThemeEngine::loadTheme()
{
	return loadDefaultTheme();
}

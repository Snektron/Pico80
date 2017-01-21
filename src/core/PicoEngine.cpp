#include "core/PicoEngine.h"

PicoEngine::PicoEngine()
{
	rootContext()->setContextProperty("Theme", mTheme.toVariant());
	rootContext()->setContextProperty("Settings", &mSettings);
	connect(&mTheme, SIGNAL(themeChanged()), this, SLOT(onThemeChanged()));
}

IPicoSettings* PicoEngine::settings()
{
	return &mSettings;
}

ITheme* PicoEngine::theme()
{
	return &mTheme;
}

IPicoQmlEngine* PicoEngine::qmlEngine()
{
	return &mQmlEngine;
}

QQmlContext* PicoEngine::rootContext()
{
	return mQmlEngine.rootContext();
}

void PicoEngine::onThemeChanged()
{
	rootContext()->setContextProperty("Theme", mTheme.toVariant());
}

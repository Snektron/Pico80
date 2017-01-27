#include "core/PicoEngine.h"
#include <QDebug>

PicoEngine::PicoEngine(QUrl url):
	mPico(&mManager)
{
	rootContext()->setContextProperty("Theme", mTheme.toVariant());
	rootContext()->setContextProperty("Settings", &mSettings);
	rootContext()->setContextProperty("Pico", &mPico);

	connect(&mTheme, SIGNAL(themeChanged()), this, SLOT(onThemeChanged()));
	connect(&mPico, SIGNAL(pluginChanged(QString)), this, SIGNAL(pluginChanged(QString)), Qt::QueuedConnection);

	mQmlEngine.load(url);
}

PluginManager* PicoEngine::pluginManager()
{
	return &mManager;
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

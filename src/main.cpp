#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QObject>
#include "Settings.h"
#include "gui/display/Display.h"
#include "Pico80.h"

#define TAG "main"

bool parseArgs()
{
	QCommandLineParser parser;
	switch (Settings::parse(parser))
	{
	case Settings::ParseResult::PR_OK:
		return false;
	case Settings::ParseResult::PR_ERROR:
		qCritical() << parser.errorText();
		return true;
	case Settings::ParseResult::PR_HELP:
		qInfo() << parser.helpText();
		return true;
	case Settings::ParseResult::PR_VERSION:
		qInfo() << QGuiApplication::applicationName();
		qInfo() << QGuiApplication::applicationVersion();
	default:
		return true;
	}
}

void registerTypes()
{
	qmlRegisterType<Display>("Pico80", 1, 0, "Display");
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
	QGuiApplication::setApplicationName("Pico80");
	QGuiApplication::setApplicationDisplayName("Pico80");
	QGuiApplication::setApplicationVersion("0");

	if (parseArgs())
		return EXIT_SUCCESS;

	registerTypes();

	Pico80 pico;
	QObject::connect(&app, SIGNAL(aboutToQuit()), &pico, SLOT(quit()));
	pico.start();

    return app.exec();
}

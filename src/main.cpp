#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <cstdint>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QObject>
#include "Settings.h"
#include "core/Logger.h"
#include "gui/Display.h"
#include "Pico80.h"

#define TAG "main"

void initLogger()
{
	auto t = time(nullptr);
	auto tm = *localtime(&t);

	std::ostringstream oss;
	oss << std::put_time(&tm, "%Y%m%d-%H%M%S.log");
	std::string logfile = oss.str();

	if (Settings::get()->saveLog)
		Logger::addPolicy(new Logger::FilePolicy(logfile));
	if (!Settings::get()->quiet)
		Logger::addPolicy(new Logger::ConsolePolicy());
}

bool parseArgs()
{
	QCommandLineParser parser;
	switch (Settings::parse(parser))
	{
	case Settings::ParseResult::PR_OK:
		return false;
	case Settings::ParseResult::PR_ERROR:
		std::cerr << qPrintable(parser.errorText()) << std::endl;
		return true;
	case Settings::ParseResult::PR_HELP:
		std::cout << qPrintable(parser.helpText()) << std::endl;
		return true;
	case Settings::ParseResult::PR_VERSION:
		std::cout << qPrintable(QGuiApplication::applicationName()) << ' ';
		std::cout << qPrintable(QGuiApplication::applicationVersion()) << std::endl;
	default:
		return true;
	}
}

void registerTypes()
{
	qmlRegisterType<Display>("Pico80", 1, 0, "Display");
	qRegisterMetaType<uint8_t>("uint8_t");
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
	QGuiApplication::setApplicationName("Pico80");
	QGuiApplication::setApplicationDisplayName("Pico80");
	QGuiApplication::setApplicationVersion("0");

	if (parseArgs())
		return EXIT_SUCCESS;
	initLogger();

	registerTypes();

	QQmlApplicationEngine engine;
	Pico80 pico(engine.rootContext());
	QObject::connect(&app, SIGNAL(aboutToQuit()), &pico, SLOT(quit()));
	engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
	pico.initialize(engine.rootObjects()[0]);
	pico.start();

    return app.exec();
}

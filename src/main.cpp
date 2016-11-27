#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>
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
	{
		if (Settings::get()->quiet)
			Logger::init(new Logger::FilePolicy(logfile));
		else
			Logger::init(new Logger::ConsoleFilePolicy(logfile));
	}else if (!Settings::get()->quiet)
		Logger::init(new Logger::ConsolePolicy());
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

	Logger::info(TAG, "Starting");

	registerTypes();

	QQmlApplicationEngine engine;
	engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

	Pico80 pico(engine.rootObjects()[0]);
	QObject::connect(&app, SIGNAL(aboutToQuit()), &pico, SLOT(quit()));
	pico.start();

    return app.exec();
}

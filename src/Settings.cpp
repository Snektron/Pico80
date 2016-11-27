#include "Settings.h"
#include <QStringList>
#include <QGuiApplication>

namespace Settings
{
	namespace
	{
		Settings settings
		{
			"rom.bin",
			true,
			false,
			false
		};
	}

	ParseResult parse(QCommandLineParser& parser)
	{
		parser.setApplicationDescription("Pico80 fantasy console");
		QCommandLineOption romOption(QStringList() << "r" << "rom",
									 "Rom file path.",
									 "path",
									 "rom.bin");
		parser.addOption(romOption);
		QCommandLineOption dsrOption(QStringList() << "n" << "dont-save",
									 "Do not save changes back to the rom file.");
		parser.addOption(dsrOption);
		QCommandLineOption quietOption(QStringList() << "q" << "quiet",
									 "Do not output log messages to console.");
		parser.addOption(quietOption);
		QCommandLineOption slOption(QStringList() << "s" << "save-log",
									 "Output log to a file.");
		parser.addOption(slOption);
		QCommandLineOption helpOption = parser.addHelpOption();
		QCommandLineOption versionOption = parser.addVersionOption();

		if (!parser.parse(QGuiApplication::arguments()))
			return ParseResult::PR_ERROR;

		if (parser.isSet(versionOption))
			return ParseResult::PR_VERSION;

		if (parser.isSet(helpOption))
			return ParseResult::PR_HELP;

		settings.rom = parser.value(romOption).toStdString();
		settings.saveRom = !parser.isSet(dsrOption);
		settings.quiet = parser.isSet(quietOption);
		settings.saveLog = parser.isSet(slOption);

		return ParseResult::PR_OK;
	}

	Settings* get()
	{
		return &settings;
	}
}

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

		QCommandLineOption helpOption = parser.addHelpOption();
		QCommandLineOption versionOption = parser.addVersionOption();

		if (!parser.parse(QGuiApplication::arguments()))
			return ParseResult::PR_ERROR;

		if (parser.isSet(versionOption))
			return ParseResult::PR_VERSION;

		if (parser.isSet(helpOption))
			return ParseResult::PR_HELP;

		settings.rom = parser.value(romOption);
		settings.saveRom = !parser.isSet(dsrOption);

		return ParseResult::PR_OK;
	}

	Settings* get()
	{
		return &settings;
	}
}

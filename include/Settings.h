#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>
#include <QCommandLineParser>

namespace Settings
{
	typedef struct Settings
	{
		std::string rom;
		bool saveRom;
		bool quiet;
		bool saveLog;
	} Settings;

	enum class ParseResult
	{
		PR_OK,
		PR_ERROR,
		PR_VERSION,
		PR_HELP
	};

	ParseResult parse(QCommandLineParser& parser);

	Settings* get();
}

#endif // SETTINGS_H

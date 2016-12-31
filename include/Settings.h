#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>
#include <QCommandLineParser>

namespace Settings
{
	typedef struct Settings
	{
		QString rom;
		bool saveRom;
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

#include <cstdlib>
#include <iostream>
#include <exception>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <SDL2/SDL.h>
#include "Pico80.h"
#include "core/Logger.h"
#include "core/Time.h"
#include "Settings.h"

#define TAG "main"

void init_logger()
{
	auto t = time(nullptr);
	auto tm = *localtime(&t);

	std::ostringstream oss;
	oss << std::put_time(&tm, "%Y%m%d-%H%M%S.log");
	std::string logfile = oss.str();

	if (Settings::log_to_file())
	{
		if (Settings::quiet())
			Logger::init(new Logger::FilePolicy(logfile));
		else
			Logger::init(new Logger::ConsoleFilePolicy(logfile));
	}else if (!Settings::quiet())
		Logger::init(new Logger::ConsolePolicy());
}

void run()
{
	init_logger();

	Logger::info(TAG, "Starting");

	Pico80 pico;
	pico.start();

	Logger::info(TAG, "Stopped");
}

int main(int argc, char* argv[])
{
	if (Settings::parse_args(argc, argv))
		run();

	return EXIT_SUCCESS;
}

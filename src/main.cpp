#include "Pico80.h"
#include <cstdlib>
#include <exception>
#include <sstream>
#include <ctime>
#include <SDL2/SDL.h>
#include <iomanip>
#include "core/Logger.h"
#include "core/Time.h"
#include "Settings.h"

#define TAG "main"

void run()
{
	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);

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

	Logger::info(TAG, "Starting");
	Logger::info(TAG) << "Logfile: " << logfile << Logger::endl;

	try{
		Pico80 pico;
		pico.run();
	}
	catch (const std::runtime_error& err)
	{
		Logger::error("Runtime error", err.what());
	}

	Logger::info(TAG, "Stopped");
}

int main(int argc, char* argv[])
{
	if (Settings::parse_args(argc, argv))
		run();
	return EXIT_SUCCESS;
}

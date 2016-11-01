#include "Pico80.h"
#include <cstdlib>
#include <iostream>
#include <exception>
#include <SDL2/SDL.h>
#include "core/Logger.h"

#define TAG "main"

// TODO seperate settings parser

int main(int argc, char* argv[])
{
	Logger::init(new Logger::ConsolePolicy());
	Logger::info(TAG, "Starting");

	try{
		Pico80 *pico = new Pico80();
		if (!pico->parseArgs(argc, argv))
			return EXIT_FAILURE;
		pico->init();
		pico->run();
		delete pico;
	}
	catch (const std::runtime_error& err)
	{
		Logger::error("Runtime error", err.what());
	}
	catch (const std::runtime_error* err)
	{
		Logger::error("Runtime error", err->what());
	}

	Logger::info(TAG, "Stopped");

	return EXIT_SUCCESS;
}

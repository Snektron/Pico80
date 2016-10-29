#include <cstdlib>
#include <iostream>
#include <exception>
#include <SDL2/SDL.h>
#include "Pico80.h"

int main(int argc, char* argv[])
{
	if (!Pico80::parse_args(argc, argv))
		return EXIT_SUCCESS;

	try{
		Pico80::init();
		Pico80::run();
		Pico80::destroy();
	}
	catch (const std::runtime_error& err)
	{
		Logger::error("Runtime error", err.what());
	}
	catch (const std::runtime_error* err)
	{
		Logger::error("Runtime error", err->what());
	}

	return EXIT_SUCCESS;
}

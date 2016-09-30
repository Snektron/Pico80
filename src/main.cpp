#include <cstdlib>
#include <iostream>
#include <exception>
#include <SDL2/SDL.h>
#include "Pico80.h"
#include "core/Logger.h"

int main(int argc, char* argv[])
{
	try{
		Pico80 pico;
		pico.start();
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

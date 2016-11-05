#include <cstdlib>
#include <SDL2/SDL.h>
#include "Pico80.h"
#include "Settings.h"

#define TAG "main"

void run()
{
	Pico80 pico;
	pico.start();
}

int main(int argc, char* argv[])
{
	if (Settings::parse_args(argc, argv))
		run();

	return EXIT_SUCCESS;
}

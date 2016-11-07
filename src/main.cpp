#include <cstdlib>
#include <memory>
#include "core/Engine.h"
#include "Pico80.h"
#include "Settings.h"

#define TAG "main"

void run()
{
	std::shared_ptr<Pico80> pico = std::make_shared<Pico80>();
	Engine::setApplication(pico);
	Engine::start();
}

int main(int argc, char* argv[])
{
	if (Settings::parse_args(argc, argv))
		run();

	return EXIT_SUCCESS;
}

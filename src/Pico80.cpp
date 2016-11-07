#include "Pico80.h"
#include <memory>
#include <sstream>
#include <ctime>
#include <iomanip>
#include "glad/glad.h"
#include "core/Logger.h"
#include "core/Input.h"
#include "core/view/View.h"
#include "core/Engine.h"
#include "emu/EmulatorView.h"
#include "Settings.h"

#define TAG "Pico80"

Pico80::Pico80():
	Application(FPS, TPS, {"Pico80", 512, 512})
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

void Pico80::onInitialize()
{
	Logger::info(TAG, "Started");

	emulator = std::make_shared<EmulatorView>();
	viewRoot = emulator;

	viewRoot->resize(0, 0, 512, 512);

	glClearColor(0.95, 0.95, 0.95, 1);
}

void Pico80::onUpdate()
{
	emulator->onTick();
}

void Pico80::onRender()
{
	glClear(GL_COLOR_BUFFER_BIT);

	viewRoot->update();
	viewRoot->render();

	if (Input::quit_requested())
		Engine::stop();
}

void Pico80::onError(const std::runtime_error& error)
{
	Logger::error("Runtime error") << error.what() << Logger::endl;
}

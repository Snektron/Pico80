#include "Pico80.h"
#include <memory>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <nanovg.h>
#include "glad/glad.h"
#include "core/Logger.h"
#include "core/Input.h"
#include "core/view/View.h"
#include "core/view/RatioView.h"
#include "core/view/MarginView.h"
#include "emu/DropdownView.h"
#include "core/Engine.h"
#include "core/Graphics.h"
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
	ViewPtr dd = std::make_shared<DropdownView>(emulator);
	ViewPtr ratio = std::make_shared<RatioView>(1, dd);
	ViewPtr margin = std::make_shared<MarginView>(0.9, ratio);
	root = margin;

	glClearColor(0.95, 0.95, 0.95, 1);
}

void Pico80::onUpdate()
{
	emulator->onTick();
}

void Pico80::onRender()
{
	root->onUpdate();

	glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	NVGcontext *vg = Graphics::nvg();
	nvgBeginFrame(vg, Graphics::getWidth(), Graphics::getHeight(), Graphics::getPixelRatio());
	root->onRender(vg);
	nvgEndFrame(vg);
}

void Pico80::onResize(int width, int height)
{
	glViewport(0, 0, width, height);
	root->onLayout(0, 0, width, height);
}

void Pico80::onMouseMoveEvent(MouseMoveEvent& event)
{
	root->onMouseMoveEvent(event);
}

void Pico80::onMouseButtonEvent(MouseButtonEvent& event)
{
	root->onMouseButtonEvent(event);
}

void Pico80::onKeyEvent(KeyEvent& event)
{
	root->onKeyEvent(event);
}

void Pico80::onError(const std::runtime_error& error)
{
	Logger::error("Runtime error") << error.what() << Logger::endl;
}

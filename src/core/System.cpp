#include "core/System.h"
#include <string>
#include "core/Graphics.h"
#include "core/Input.h"
#include "core/Logger.h"
#include "core/Time.h"
#include "core/Display.h"

#define TAG "System"

void System::init(std::string name, int w, int h)
{
	Logger::init(new Logger::ConsolePolicy());
	Logger::info(TAG, "Starting");
	Graphics::init(name, w, h);
	Display::init();
}

void System::destroy()
{
	Logger::info(TAG, "Stopping");
	Display::destroy();
	Graphics::destroy();
}

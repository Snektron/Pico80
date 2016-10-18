#include <string>
#include "core/System.h"
#include "core/Graphics.h"
#include "core/Input.h"
#include "core/Logger.h"
#include "core/Time.h"

#define TAG "System"

void System::init(std::string name, int w, int h)
{
	Logger::init(new Logger::ConsolePolicy());
	Logger::info(TAG, "Starting");
	Time::init();
	Graphics::init(name, w, h);
}

void System::destroy()
{
	Logger::info(TAG, "Stopping");
	Graphics::destroy();
}

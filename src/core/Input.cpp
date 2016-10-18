#include <SDL2/SDL.h>
#include "core/Input.h"
#include "core/Logger.h"
#include "core/Graphics.h"

#define TAG "Input"

namespace
{
	bool quit = false;
}

void Input::update()
{
	SDL_Event event;
	while(SDL_PollEvent(&event) != 0)
		handleEvent(&event);
}

void Input::handleEvent(SDL_Event* event)
{
	switch(event->type)
	{
	case SDL_QUIT:
		Logger::info(TAG, "Requesting quit");
		quit = true;
		break;
	case SDL_WINDOWEVENT:
		if (event->window.event == SDL_WINDOWEVENT_RESIZED)
		{
			Logger::info(TAG) << "Window resized: "
					<< event->window.data1 << "x"
					<< event->window.data2 << Logger::endl;
			Graphics::refresh_surface();
		}
	}
}

bool Input::quitRequested()
{
	return quit;
}

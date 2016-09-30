#include <exception>
#include <SDL2/SDL.h>
#include "core/Graphics.h"
#include "core/Logger.h"

#define TAG "Graphics"

SDL_Window *window;
SDL_Surface *surface;

void Graphics::init(int w, int h)
{
	Logger::info(TAG, "Initializing graphics");

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		Logger::error(TAG) << "Failed to initialize SDL: " << SDL_GetError() << Logger::endl;
		throw std::runtime_error("Failed to initialize graphics");
	}

	window = SDL_CreateWindow("Pico80",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			w, h, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	if (window == NULL)
	{
		Logger::error(TAG) << "Failed to create window: " << SDL_GetError() << Logger::endl;
		throw std::runtime_error("Failed to initialize graphics");
	}

	refresh_surface();

	Logger::info(TAG, "Graphics initialized.");
}

void Graphics::update()
{
	SDL_UpdateWindowSurface(window);
}

void Graphics::destroy()
{
	Logger::info("Graphics", "Destroying graphics");

	SDL_FreeSurface(surface);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Graphics::refresh_surface()
{
	if (surface)
		SDL_FreeSurface(surface);

	surface = SDL_GetWindowSurface(window);
	if (surface == NULL)
	{
		Logger::error(TAG) << "Failed initialize surface: " << SDL_GetError() << Logger::endl;
		throw std::runtime_error("Failed to initialize graphics");
	}
}

void Graphics::clear()
{
	SDL_FillRect(surface, NULL, 0);
}

int Graphics::get_width()
{
	return surface->w;
}

int Graphics::get_height()
{
	return surface->h;
}

SDL_Window* Graphics::get_window()
{
	return window;
}

SDL_Surface* Graphics::get_surface()
{
	return surface;
}

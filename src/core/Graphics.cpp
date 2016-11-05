#include "core/Graphics.h"
#include <exception>
#include <string>
#include <memory>
#include <SDL2/SDL.h>
#include "core/Logger.h"

#define TAG "Graphics"

namespace
{
	SDL_Window *window;
	std::unique_ptr<SDL_Surface> surface;
}

SDL_Window* create_window(std::string title, int w, int h, uint32_t flags)
{
	return SDL_CreateWindow(title.c_str(),
				SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED,
				w, h, flags);
}

void Graphics::init(std::string name, int w, int h)
{
	Logger::info(TAG, "Initializing graphics");

	window = create_window(name, w, h, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	if (!window)
	{
		Logger::error(TAG) << "Failed to create window: " << SDL_GetError() << Logger::endl;
		throw std::runtime_error("Failed to initialize graphics");
	}

	refresh_surface();
}

void Graphics::destroy()
{
	Logger::info(TAG, "Destroying graphics");

	SDL_FreeSurface(surface.release());

	SDL_DestroyWindow(window);
}

void Graphics::update()
{
	SDL_UpdateWindowSurface(window);
}

void Graphics::refresh_surface()
{
	if (surface)
		SDL_FreeSurface(surface.release());

	std::unique_ptr<SDL_Surface> sf(SDL_GetWindowSurface(window));
	surface = std::move(sf);

	if (!surface)
	{
		Logger::error(TAG) << "Failed initialize surface: " << SDL_GetError() << Logger::endl;
		throw std::runtime_error("Failed to initialize graphics");
	}
}

void Graphics::clear()
{
	SDL_FillRect(surface.get(), NULL, 0);
}

void Graphics::blit(SDL_Surface *src, SDL_Rect& dstrect)
{
	SDL_BlitScaled(src, NULL, surface.get(), &dstrect);
}

int Graphics::get_width()
{
	return surface->w;
}

int Graphics::get_height()
{
	return surface->h;
}

#include "RenderWindow.h"

RenderWindow::~RenderWindow()
{
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	m_renderer = NULL;
	m_window = NULL;
}

bool RenderWindow::initRenderWindow(const char* title, int width, int height)
{
	bool success = true;

	m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

	if (m_window == NULL)
	{
		std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << '\n';
		success = false;
	}
	else
	{
		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		if (m_renderer == NULL)
		{
			std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << '\n';
			success = false;
		}
	}

	return success;
}

SDL_Texture* RenderWindow::loadTexture(const char* path)
{
	SDL_Texture* texture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path);
	if (loadedSurface == NULL)
		std::cout << "Unable to load image " << path << "! SDL_Image Error: " << IMG_GetError() << '\n';
	else
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		texture = SDL_CreateTextureFromSurface(m_renderer, loadedSurface);
		if (texture == NULL)
			std::cout << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << '\n';

		SDL_FreeSurface(loadedSurface);
	}

	return texture;
}

void RenderWindow::clearRender()
{
	SDL_SetRenderDrawColor(m_renderer, 100, 100, 100, 0xFF);
	SDL_RenderClear(m_renderer);
}

void RenderWindow::render()
{
	SDL_RenderPresent(m_renderer);
}
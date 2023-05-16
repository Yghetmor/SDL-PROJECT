#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class RenderWindow
{
public:
	RenderWindow()
		: m_window{ NULL }, m_renderer{ NULL } {}
	~RenderWindow();

	bool initRenderWindow(const char* title, int width, int height);

	SDL_Texture* loadTexture(const char* path);
	void clearRender();
	void render();

	SDL_Renderer* getRenderer() { return m_renderer; }

private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
};
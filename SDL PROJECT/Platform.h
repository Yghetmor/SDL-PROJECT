#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Clock.h"

class Platform
{
public:
	static const int MOVE_SPEED = 80;

	Platform(float x, int y, int number, SDL_Texture* tex);
	~Platform();

	void render(SDL_Renderer* renderer);
	void move(Clock& clock);

	const SDL_Rect getRect() const { return m_rect; }

private:
	float m_x;
	int m_y;
	int m_number;					// width in blocks
	SDL_Rect m_rect;
	SDL_Texture* m_texture;
};
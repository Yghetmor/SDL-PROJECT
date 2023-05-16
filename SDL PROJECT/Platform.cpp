#include "Platform.h"

Platform::Platform(float x, int y, int number, SDL_Texture* tex)
	: m_x{ x }, m_y{ y }, m_texture{ tex }, m_number { number }, m_rect{ static_cast<int>(x), y, number * 15, 30
} {}

Platform::~Platform()
{
	if (m_texture != NULL)
	{
		m_texture = NULL;
	}
}

void Platform::render(SDL_Renderer* renderer)
{
	SDL_Rect grassSrc{ 17, 17, 15, 15 };
	SDL_Rect dirtSrc{ 0, 17, 15, 15 };
	SDL_Rect block{ m_x, m_y, 15, 15 };

	for (size_t i{}; i < m_number; ++i)
	{
		SDL_RenderCopy(renderer, m_texture, &grassSrc, &block);
		block.x += 15;
	}

	block.x = m_x;
	block.y += 15;

	for (size_t i{}; i < m_number; ++i)
	{
		SDL_RenderCopy(renderer, m_texture, &dirtSrc, &block);
		block.x += 15;
	}
}

void Platform::move(Clock& clock)
{
	m_x -= MOVE_SPEED * clock.getDelta();
	m_rect.x = static_cast<int>(m_x);
}
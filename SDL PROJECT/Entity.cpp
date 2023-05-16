#include "Entity.h"

Entity::Entity(int x, float y, int width, int height, SDL_Texture* tex)
	: m_x{ x }, m_y{ y }, m_texture{ tex }, m_rect{ x, static_cast<int>(y), width, height } {}

Entity::~Entity()
{
	if (m_texture != NULL)
	{
		SDL_DestroyTexture(m_texture);
		m_texture = NULL;
	}
}

void Entity::render(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, m_texture, NULL, &m_rect);
}

void Entity::handleEvent(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_UP: 
			if (!isJumping())
				m_VelY = -JUMP_SPEED;
			break;
		case SDLK_LEFT: m_VelX -= SPEED; break;
		case SDLK_RIGHT: m_VelX += SPEED; break;
		}
	}
	if (event.type == SDL_KEYUP && event.key.repeat == 0)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_LEFT: m_VelX += SPEED; break;
		case SDLK_RIGHT: m_VelX -= SPEED; break;
		}
	}
}

void Entity::move(Clock& clock, const std::vector<Platform*>& plat)
{
	m_x += m_VelX;
	m_rect.x += m_VelX;

	if ((m_x < 0) || (m_x + m_rect.w > 640) || (checkCollision(plat) && m_VelY > 0))
	{
		m_x -= m_VelX;
		m_rect.x -= m_VelX;
	}

	float tempY{ m_y };
	m_y += m_VelY * clock.getDelta();
	m_rect.y = static_cast<int>(m_y);

	if (m_y + m_rect.h > 480)
	{
		m_y = m_rect.y = 480 - m_rect.h;
		m_VelY = 0.0f;
	}

	if (checkCollision(plat) && m_VelY > 0)
	{
		m_y = m_rect.y = tempY;
		m_VelY = 0.0f;
	}
}

void Entity::update(Clock& clock, const std::vector<Platform*>& plat)
{
	m_VelY += Y_GACCEL * clock.getDelta();

	if (m_VelY > MAX_Y_VEL)
		m_VelY = MAX_Y_VEL;

	move(clock, plat);

	if (m_VelY <= 50 && m_VelY >= 0)
		m_jumping = false;
	else
		m_jumping = true;
}

bool Entity::checkCollision(const std::vector<Platform*>& plat)
{
	for (const auto& platform : plat)
	{
		if (m_rect.y + m_rect.h <= platform->getRect().y)
			continue;
		else if (m_rect.y >= platform->getRect().y + platform->getRect().h)
			continue;
		else if (m_rect.x + m_rect.w <= platform->getRect().x)
			continue;
		else if (m_rect.x >= platform->getRect().x + platform->getRect().w)
			continue;
		else
			return true;
	}

	return false;
}
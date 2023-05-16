#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include "Clock.h"
#include "Platform.h"

class Entity
{
public:
	static const int SPEED = 2;
	static const int MAX_Y_VEL = 440;
	static const int Y_GACCEL = 1300;
	static const int JUMP_SPEED = 720;

	Entity(int x, float y, int width, int height, SDL_Texture* tex);
	~Entity();

	void render(SDL_Renderer* renderer);
	void handleEvent(SDL_Event& event);
	void move(Clock& clock, const std::vector<Platform*>& plat);
	void update(Clock& clock, const std::vector<Platform*>& plat);
	bool checkCollision(const std::vector<Platform*>& plat);

	bool isJumping() { return m_jumping; }

private:
	int m_x;
	float m_y;
	int m_VelX{ 0 };
	float m_VelY{ 0.0f };
	int m_AccY{ 0 };
	bool m_jumping{};
	SDL_Rect m_rect;
	SDL_Texture* m_texture;
};
#pragma once
#include <SDL.h>

class Clock
{
public:
	void tick()
	{
		int tickTime = SDL_GetTicks();
		m_delta = tickTime - m_lastTickTime;
		m_lastTickTime = tickTime;
	}

	float getDelta() { return static_cast<float>(m_delta) / 1000; }

private:
	int m_lastTickTime{};
	int m_delta{};
};
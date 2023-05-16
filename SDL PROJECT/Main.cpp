#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include "RenderWindow.h"
#include "Entity.h"
#include "Platform.h"
#include "Clock.h"
#include "RandomNumber.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
void close();
void cleanUpPlatforms(std::vector<Platform*>& platforms);
void makeNewPlatform(std::vector<Platform*>& platforms, SDL_Texture* tex);

int main(int argc, char* args[])
{
	if (!init())
		std::cout << "Failed to initialize!\n";
	else
	{
		RenderWindow window;
		if (!window.initRenderWindow("Testing", SCREEN_WIDTH, SCREEN_HEIGHT))
		{
			std::cout << "Failed to render window!\n";
		}
		else
		{
			bool gameRunning = true;

			SDL_Event event;

			SDL_Texture* blobTexture = window.loadTexture("Resources/blob_creature.png");
			SDL_Texture* platformTexture = window.loadTexture("Resources/dirt_block.png");
			SDL_Texture* backgroundTexture = window.loadTexture("Resources/background.png");

			Entity blob(SCREEN_WIDTH / 2, static_cast<float>(SCREEN_HEIGHT / 2), 40, 40, blobTexture);
			Platform* plat1 = new Platform(400, 250, 10, platformTexture);
			Platform* plat2 = new Platform(150, 400, 10, platformTexture);

			std::vector<Platform*> platforms{ plat1, plat2 };

			Clock clock;

			while (gameRunning)
			{
				while (SDL_PollEvent(&event))
				{
					if (event.type == SDL_QUIT)
						gameRunning = false;

					blob.handleEvent(event);
				}

				window.clearRender();

				clock.tick();

				cleanUpPlatforms(platforms);

				if (platforms.size() < 3)
					makeNewPlatform(platforms, platformTexture);

				blob.update(clock, platforms);

				SDL_RenderCopy(window.getRenderer(), backgroundTexture, NULL, NULL);

				for (const auto plat : platforms)
				{
					plat->move(clock);
					plat->render(window.getRenderer());
				}

				blob.render(window.getRenderer());

				window.render();
			}

			SDL_DestroyTexture(platformTexture);
			platformTexture = nullptr;
		}


	}

	close();
	return 0;
}

bool init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		std::cout << "SDL could not initialize. Error: " << SDL_GetError() << '\n';
		success = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
			std::cout << "Warning: Linear texture filtering not enabled!\n";
	}

	if (!(IMG_Init(IMG_INIT_PNG)))
	{
		std::cout << "SDL_Image could not initialize. Error: " << IMG_GetError() << '\n';
		success = false;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "SDL_Mixer could not initialize. Error: " << Mix_GetError() << '\n';
		success = false;
	}

	return success;
}

void close()
{
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

void cleanUpPlatforms(std::vector<Platform*>& platforms)
{
	for (auto iter{ platforms.begin() }; iter < platforms.end(); ++iter)
	{
		if (((*iter)->getRect().x + (*iter)->getRect().w) < 0)
		{
			delete (*iter);
			*iter = nullptr;
			iter = platforms.erase(iter);

			if (iter == platforms.end())
				return;
		}
	}
}

void makeNewPlatform(std::vector<Platform*>& platforms, SDL_Texture* tex)
{
	auto random = createUniformPseudoRandomNumberGenerator(50, 420);
	platforms.push_back(new Platform(SCREEN_WIDTH, random(), 10, tex));
}

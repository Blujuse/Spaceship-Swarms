#include "enemiesmanager.h"

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <list>

#include "bulletmanager.h"

void EnemiesManager::EnemiesInit() 
{
	// Loading enemies image and creating texture from it
	SDL_Surface* surface = IMG_Load("./Assets/Player/Placeholder.png");
	this->enemiesTexture = SDL_CreateTextureFromSurface(this->renderer, surface);
	SDL_FreeSurface(surface);

	// Goes through and creates enemies until the maximum number of them has been reached
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		// Spawns enemies randomly within set area, in this case 800 x 640
		enemies.push_back(Enemies{ rand() % 800, rand() % 640 });
	}
}

void EnemiesManager::EnemiesUpdate()
{
	// For each of the ememies do the stuff below
	for (auto& m : enemies)
	{
		// Move to the right each frame
		m.x += 1;

		// Checks the x position of the enemies, and wraps them when the leave the screen
		if (m.x > 800 + 32)
		{
			m.x = -32;
		}

		// Checks if the bullets from the bullet script collide with the enemies
		for (auto& b : bulletManager->bullets)
		{
			// Creating two local SDL_Rects one for bullets and one for enemies
			SDL_Rect bulletRect = { b.x, b.y, 10, 10 };
			SDL_Rect enemiesRect = { m.x, m.y, 32, 32 };

			// One null as IntersectRect takes 3 arguments, it will be the result of bullets and enemies intersection
			SDL_Rect nullRect;

			// If the bulletes and enemies intersect, mark the bullet for removal and the enemy as destroyed
			if (SDL_IntersectRect(&bulletRect, &enemiesRect, &nullRect))
			{
				b.distance = 1000;
				m.x = 0xCCCCCCCC;
			}
		}
	}

	// If the size of the enemies vector is less than the maximum allowed spawn more
	if (enemies.size() < MAX_ENEMIES)
	{
		enemies.push_back(Enemies{ -32, rand() % 640 });
	}

	// Remove the enemies on collision
	auto remove = std::remove_if(enemies.begin(), enemies.end(), [](const Enemies& m) { return m.x == 0xCCCCCCCC; });
	enemies.erase(remove, enemies.end());
}

void EnemiesManager::EnemiesDraw()
{
	// For each of the emeies in the vector draw them on the screen
	for (auto& m : enemies)
	{
		SDL_Rect dest = { m.x, m.y, 32,32, };
		SDL_RenderCopy(renderer, enemiesTexture, 0, &dest);
	}
}

void EnemiesManager::EnemiesClean()
{
	// Cleaning
	SDL_DestroyTexture(this->enemiesTexture);
}

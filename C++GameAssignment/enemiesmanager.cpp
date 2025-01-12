#include "enemiesmanager.h"

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <list>
#include <ctime>

#include "bulletmanager.h"

void EnemiesManager::Spawner() 
{
	int edgeSpawn = rand() % 4;

	Enemies enemy;

	switch (edgeSpawn)
	{
	case 0: // Spawn from top
		enemy.x = rand() % 800;
		enemy.y = -32;  // Just above the screen
		enemy.velocityX = 0;  // No horizontal movement
		enemy.velocityY = 1;  // Moving down
		break;
	case 1: // Spawn from bottom
		enemy.x = rand() % 800;
		enemy.y = 640 + 32;  // Just below the screen
		enemy.velocityX = 0;  // No horizontal movement
		enemy.velocityY = -1;  // Moving up
		break;
	case 2: // Spawn from left
		enemy.x = -32;  // Just left of the screen
		enemy.y = rand() % 640;
		enemy.velocityX = 1;  // Moving right
		enemy.velocityY = 0;  // No vertical movement
		break;
	case 3: // Spawn from right
		enemy.x = 800 + 32;  // Just right of the screen
		enemy.y = rand() % 640;
		enemy.velocityX = -1;  // Moving left
		enemy.velocityY = 0;  // No vertical movement
		break;
	}

	// Spawns enemies randomly within set area, in this case 800 x 640
	enemies.push_back(enemy);
}

void EnemiesManager::EnemiesInit() 
{
	srand(time(0));  // Start the random number generator

	// Loading enemies image and creating texture from it
	SDL_Surface* surface = IMG_Load("./Assets/Tilemap/Asteroid.png");
	this->enemiesTexture = SDL_CreateTextureFromSurface(this->renderer, surface);
	SDL_FreeSurface(surface);

	// Initialise the sounds
	soundPlayer = new SoundPlayer();

	// Initialise the particles
	particles = new Particles(renderer);

	// Goes through and creates enemies until the maximum number of them has been reached
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		Spawner();
	}
}

void EnemiesManager::EnemiesUpdate(ScoreManager* scoreManager)
{
	// For each of the ememies do the stuff below
	for (auto& m : enemies)
	{
		// Move to the right each frame
		m.x += m.velocityX;
		m.y += m.velocityY;

		// If the enemy goes off-screen, destroy it
		if (m.x < -32 || m.x > 800 + 32 || m.y < -32 || m.y > 640 + 32)
		{
			m.x = 0xCCCCCCCC;  // Mark for removal
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
				// Create particles at the enemy's current position
				particles->ParticleStart(m.x + 8, m.y + 8); // Center of the enemy

				b.distance = 1000;
				m.x = 0xCCCCCCCC;
				scoreManager->AddScore(10);

				// Play Sound on destruction
				soundPlayer->PlaySound(Sounds::ASTEROID_BREAK);
			}
		}
	}

	// Update the particles to move them
	particles->ParticleUpdate();

	// If the size of the enemies vector is less than the maximum allowed spawn more
	if (enemies.size() < MAX_ENEMIES)
	{
		Spawner();
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

	// Render Particles
	particles->ParticleRender(renderer);
}

void EnemiesManager::EnemiesClean()
{
	// Cleaning
	SDL_DestroyTexture(this->enemiesTexture);

	if (soundPlayer != nullptr)
	{
		delete soundPlayer;

		soundPlayer = nullptr;
	}

	if (particles != nullptr)
	{
		delete particles;

		particles = nullptr;
	}
}

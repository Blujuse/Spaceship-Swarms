#include "enemiesmovement.h"
#include <iostream>

EnemiesMovement::EnemiesMovement(SDL_Renderer* renderer, Tilemap* map, Player* player)
{
	// Initialising variables
	this->renderer = renderer;
	this->map = map;
	this->player = player;
}

void EnemiesMovement::EnemiesInit(int spawnX, int spawnY)
{
	// Loading image for enemies
	SDL_Surface* surface = IMG_Load("./Assets/Enemy/Alien.png");
	this->enemy = SDL_CreateTextureFromSurface(this->renderer, surface);
	SDL_FreeSurface(surface);

	// Loading image for tile selection (when the player clicks a tile)
	surface = IMG_Load("./Assets/Player/Placeholder.png");
	this->selectionTile = SDL_CreateTextureFromSurface(this->renderer, surface);
	SDL_FreeSurface(surface);

	// Selects an image for drawing a path from enemy to selected tile
	surface = IMG_Load("./Assets/Player/Placeholder.png");
	this->pathSelected = SDL_CreateTextureFromSurface(this->renderer, surface);
	SDL_FreeSurface(surface);

	enemyX = spawnX;
	enemyY = spawnY;

	speedIncreaser = 1.0f;
}

void EnemiesMovement::MoveToPlayer()
{
	// Makes sure selected tile is 32 x 32 pixels
	selectionX = player->getPosX() / 32;
	selectionY = player->getPosY() / 32;

	// Start running A*
	runAStar = true;
}

void EnemiesMovement::EnemiesUpdate()
{
	// Gets time since SDL has been initialised
	if (SDL_GetTicks() - lastUpdate > static_cast<unsigned int>(500 / speedIncreaser)) // Using lastUpdate unsigned as SDL_GetTicks() returns an unsigned int
	{
		lastUpdate = SDL_GetTicks();

		// Increase the speed over time
		speedIncreaser += 0.01f;

		// Checks if the selection is within the tilemap
		if (selectionX >= 0 && selectionY >= 0)
		{
			// Sets the current enemy location
			Node enemy;
			enemy.x = enemyX;
			enemy.y = enemyY;

			// Sets the destination
			Node dest;
			dest.x = selectionX;
			dest.y = selectionY;

			// Only run the algorithm if needed
			if (runAStar)
			{
				// The path should be the distance between the enemy and the destination
				// The path is figured out through the A* algorithm
				path = aStar(*map, enemy, dest);

				// Stop running it, so it is only run once
				runAStar = false;
			}

			// Move to next tile
			if (path.size() > 1)
			{
				enemyX = path[1].x;
				enemyY = path[1].y;

				path.erase(path.begin());
			}

		}
	}

	// Update animation frame
	if (SDL_GetTicks() - lastAniUpdate > aniSpeed)
	{
		lastAniUpdate = SDL_GetTicks();
		currentFrame = (currentFrame + 1) % totalFrames;
	}

	//std::cout << "Enemy: (" << enemyX << ", " << enemyY << ") | Selection: (" << selectionX << ", " << selectionY << ")\n";

	if (enemyX == selectionX && enemyY == selectionY)
	{
		SET_GAME_STATE = 2;
		//std::cout << "SET TO TWO IN ENEMIESMOVEMENT\n";
	}
}

void EnemiesMovement::EnemiesDraw()
{
	// Draw selection tile
	SDL_Rect dest = { selectionX * 32, selectionY * 32, 32, 32 };
	//SDL_RenderCopy(renderer, selectionTile, 0, &dest);

	// Calculate the row and column for the current frame
	int row = currentFrame / 2; // 2 frames per row
	int col = currentFrame % 2; // Column index within the row

	// Source rectangle for the current frame
	SDL_Rect src = { col * spriteW, row * spriteH, spriteW, spriteH };

	// Draw enemy in the correct position
	dest = { enemyX * 32, enemyY * 32, 32, 32 };
	SDL_RenderCopy(renderer, enemy, &src, &dest);

	// Shows the path to the destination
	/*for (Node& n : path)
	{
		dest = { n.x * 32, n.y * 32, 32, 32 };
		SDL_RenderCopy(renderer, pathSelected, 0, &dest);
	}*/
}

void EnemiesMovement::EnemiesClean()
{
	SDL_DestroyTexture(enemy); // Free up memory
}

// USED TO SEND THE CHANGE OF STATE TO GAME HANDLER
int EnemiesMovement::GameStateUpdate()
{
	return SET_GAME_STATE;
}

int EnemiesMovement::ReturnPlayerTileX()
{
	return selectionX;
}

int EnemiesMovement::ReturnPlayerTileY()
{
	return selectionY;
}
#include "enemiesmovement.h"

EnemiesMovement::EnemiesMovement(SDL_Renderer* renderer, Tilemap* map, Player* player)
{
	// Initialising variables
	this->renderer = renderer;
	this->map = map;
	this->player = player;
}

void EnemiesMovement::EnemiesInit()
{
	// Loading image for enemies
	SDL_Surface* surface = IMG_Load("./Assets/Player/Placeholder.png");
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
}

void EnemiesMovement::MoveToPlayer()
{
	// Checks if player is moving before running A* so AStar isnt always active
	if (player->getMovingBool() == true)
	{
		// Makes sure selected tile is 32 x 32 pixels
		selectionX = player->getPosX() / 32;
		selectionY = player->getPosY() / 32;

		// Start running A*
		runAStar = true;
	}
}

void EnemiesMovement::EnemiesUpdate()
{
	// Gets time since SDL has been initialised
	if (SDL_GetTicks() - lastUpdate > 500) // Using lastUpdate unsigned as SDL_GetTicks() returns an unsigned int
	{
		lastUpdate = SDL_GetTicks();

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
}

void EnemiesMovement::EnemiesDraw()
{
	// Draw selection tile
	SDL_Rect dest = { selectionX * 32, selectionY * 32, 32, 32 };
	SDL_RenderCopy(renderer, selectionTile, 0, &dest);

	// Draw enemy in the correct position
	dest = { enemyX * 32, enemyY * 32, 32, 32 };
	SDL_RenderCopy(renderer, enemy, 0, &dest);

	// Shows the path to the destination
	for (Node& n : path)
	{
		dest = { n.x * 32, n.y * 32, 32, 32 };
		SDL_RenderCopy(renderer, pathSelected, 0, &dest);
	}
}

void EnemiesMovement::EnemiesClean()
{
	SDL_DestroyTexture(enemy); // Free up memory
}

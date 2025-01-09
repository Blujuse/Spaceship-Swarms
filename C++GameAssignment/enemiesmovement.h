#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include "enemiesastarsearch.h"
#include "tilemap.h"
#include "player.h"

class EnemiesMovement
{
public:
	EnemiesMovement(SDL_Renderer* renderer, Tilemap* map, Player* player);

	void EnemiesInit();

	void MoveToPlayer();

	void EnemiesUpdate();

	void EnemiesDraw();

	void EnemiesClean();

private:
	
	SDL_Renderer* renderer;
	SDL_Texture* enemy;
	Tilemap* map;
	SDL_Texture* selectionTile;

	SDL_Texture* pathSelected;

	Player* player;

	int selectionX = -1, selectionY = -1;
	int enemyX = 1, enemyY = 1;
	unsigned int lastUpdate = 0;

	std::vector<Node> path;

	bool runAStar = false;
};
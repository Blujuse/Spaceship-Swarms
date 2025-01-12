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

	void EnemiesInit(int spawnX, int spawnY);

	void MoveToPlayer();

	void EnemiesUpdate();

	void EnemiesDraw();

	void EnemiesClean();

	int GameStateUpdate();

	int ReturnPlayerTileX();

	int ReturnPlayerTileY();

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

	// Animation Variables

	int spriteW = 32; // Width of current frame
	int spriteH = 32; // Height of current frame
	int currentFrame = 0;
	int totalFrames = 4;

	unsigned int lastAniUpdate = 0;
	unsigned int aniSpeed = 100; // Milliseconds

	int SET_GAME_STATE = 1;

	float speedIncreaser = 1.0f;
};
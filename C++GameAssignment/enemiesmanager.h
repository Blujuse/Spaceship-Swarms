#pragma once

#include <SDL.h>
#include <vector>

#include "bulletmanager.h"

// Group enemy variables together
struct Enemies 
{
	int x, y;
};

class EnemiesManager
{

public:

	EnemiesManager(SDL_Renderer* renderer, BulletManager* bulletManager) : renderer(renderer), bulletManager(bulletManager), enemiesTexture(nullptr) {}
	virtual ~EnemiesManager() {}

	void EnemiesInit();

	void EnemiesUpdate();

	void EnemiesDraw();

	void EnemiesClean();

private:

	std::vector<Enemies> enemies;
	SDL_Renderer* renderer;
	SDL_Texture* enemiesTexture;

	BulletManager* bulletManager;

	const int MAX_ENEMIES = 16;
};
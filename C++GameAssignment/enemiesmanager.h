#pragma once

#include <SDL.h>
#include <vector>

#include "bulletmanager.h"
#include "scoremanager.h"
#include "soundplayer.h"
#include "particles.h"

// Group enemy variables together
struct Enemies 
{
	int x, y;
	int velocityX, velocityY;
};

class EnemiesManager
{

public:

	EnemiesManager(SDL_Renderer* renderer, BulletManager* bulletManager) : renderer(renderer), bulletManager(bulletManager), enemiesTexture(nullptr), particles(nullptr), soundPlayer(nullptr) {}
	virtual ~EnemiesManager() {}

	void Spawner();

	void EnemiesInit();

	void EnemiesUpdate(ScoreManager* scoreManager);

	void EnemiesDraw();

	void EnemiesClean();

private:

	std::vector<Enemies> enemies;
	SDL_Renderer* renderer;
	SDL_Texture* enemiesTexture;

	BulletManager* bulletManager;

	SoundPlayer* soundPlayer;

	Particles* particles;

	const int MAX_ENEMIES = 16;
};
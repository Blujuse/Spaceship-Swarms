#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <vector>
#include <math.h>
#include <algorithm>

#include "player.h"

#define PI 3.14159265

// struct used to group bullet variables together
struct Bullet
{
	float x = 0;
	float y = 0;
	float rotation = 0;
	float distance = 0;
	bool active = false;
};

class BulletManager
{
	friend class EnemiesManager;

public:
	BulletManager(SDL_Renderer* renderer, Player* player) : renderer(renderer), player(player), bulletTexture(nullptr) {}
	
	void BulletInit();
	
	void BulletUpdate();

	void BulletInput(const Uint8* keyDown);

	void BulletDraw();

	void BulletClean();

private:
	SDL_Renderer* renderer;
	SDL_Texture* bulletTexture;

	static const int MAX_BULLETS = 5;
	std::vector<Bullet> bullets;

	Player* player;

	const int SHOOT_TIMER_MS = 300;
	unsigned int lastShot = 0;
	const int BULLET_VELOCITY = 15;
};
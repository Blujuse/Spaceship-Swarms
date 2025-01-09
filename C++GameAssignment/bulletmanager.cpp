#include "bulletmanager.h"

// Initialising the bullet with a specific texture
void BulletManager::BulletInit()
{
	SDL_Surface* surface = IMG_Load("./Assets/Player/Placeholder.png");
	this->bulletTexture = SDL_CreateTextureFromSurface(this->renderer, surface);
	SDL_FreeSurface(surface);

	bullets.resize(MAX_BULLETS); // Preallocate bullets
}

//  Do this every frame for the bullet, moves them along
void BulletManager::BulletUpdate()
{
	// For each of the current bullets do the stuff below
	for (auto& b : bullets)
	{
		if (b.active)
		{
			// Working out the angle to shoot the bullets at
			float angleRadians = b.rotation * (M_PI / 180.0f);

			// cos and sin used to be opposite but it messed up bullet shooting? 
			// flipped them now they work?
			b.x += cos(angleRadians) * BULLET_VELOCITY;
			b.y += sin(angleRadians) * BULLET_VELOCITY;
			b.distance += BULLET_VELOCITY;

			if (b.distance > 1000)
			{
				b.active = false;
			}
		}
	}

	/*
	// Bullets are removed when they travel a specified distance fromt he player
	auto remove = std::remove_if(bullets.begin(), bullets.end(), [](const Bullet& b) { return b.distance > 1000; });
	bullets.erase(remove, bullets.end());
	*/
}

// Shoot bullets using the specified input key
void BulletManager::BulletInput(const Uint8* keystate)
{
	if (keystate[SDL_SCANCODE_SPACE])
	{
		if (SDL_GetTicks() - lastShot > SHOOT_TIMER_MS)
		{
			for (auto& b : bullets)
			{
				if (!b.active) 
				{
					b.x = player->getPosX();
					b.y = player->getPosY();
					b.rotation = player->getAngle() - 90.0f;
					b.distance = 0.0f;
					b.active = true;
					lastShot = SDL_GetTicks();
					break;
				}
			}

			/*
			// Start moving the bullet, contains the spawn location and to fire at
			bullets.push_back(Bullet{ player->getPosX(), player->getPosY(), player->getAngle() - 90.0f, 0.0});
			lastShot = SDL_GetTicks();
			*/
		}
	}
}

// Drawing bullets on screen
void BulletManager::BulletDraw()
{
	SDL_Rect destTemp = { 0, 0, 30, 30 };
	SDL_Point center = { 5, 5 };
	for (const auto& b : bullets)
	{
		if (b.active)
		{
			SDL_Rect dest = destTemp;
			dest.x = b.x;
			dest.y = b.y;
			SDL_RenderCopyEx(renderer, bulletTexture, 0, &dest, b.rotation, &center, SDL_FLIP_NONE);
		}
	}
}

// Free up memory
void BulletManager::BulletClean()
{
	SDL_DestroyTexture(this->bulletTexture);
}
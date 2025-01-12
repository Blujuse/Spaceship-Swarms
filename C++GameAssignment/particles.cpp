#include "particles.h"

#include <iostream>

Particles::Particles(SDL_Renderer* renderer)
{
	SDL_Surface* particle = IMG_Load("./Assets/Tilemap/AsteroidDebris.png"); // Get texture

	// Check existance
	if (particle == nullptr)
	{
		std::cout << "Error loading debris png, Check it exists\n";

		throw std::runtime_error("Missing particle texture file");
	}

	particleTex = SDL_CreateTextureFromSurface(renderer, particle); // Create texture

	// Set particles to img width and height
	particleW = particle->w;
	particleH = particle->h;

	SDL_FreeSurface(particle); // Free surface to save memory
}

Particles::~Particles()
{
	SDL_DestroyTexture(particleTex);
}

void Particles::ParticleStart(int spawnPosX, int spawnPosY)
{
	// Spawn particles
	if (SDL_GetTicks() - lastParticleSpawnTime >= nextParticleSpawnTime)
	{
		lastParticleSpawnTime = SDL_GetTicks();

		nextParticleSpawnTime = emissionRate + (rand() % emissionRange); // Spawn randomly

		// Spawn certain number of particles
		for (int i = 0; i < 5; i++) 
		{
			// Using struct from header
			Particle particle;

			// Spawn at certain position
			particle.x = spawnPosX;
			particle.y = spawnPosY;

			// Random angle and speed
			float angle = (rand() % 360) * (M_PI / 180.0f);
			float speed = 2.0f + static_cast<float>(rand() % 100) / 50.0f;

			// Set speed
			particle.velX = speed * std::cos(angle);
			particle.velY = speed * std::sin(angle);

			particle.life = SDL_GetTicks() +4000; // Particles last for 4 seconds

			particles.push_back(particle);
		}
	}
}

void Particles::ParticleUpdate()
{
	// Update particles
	for (auto& particle : particles)
	{
		// Update movement with previous set speed
		particle.x += particle.velX;
		particle.y += particle.velY;
	}

	Uint32 currentTime = SDL_GetTicks();

	// Remove particles that live past life
	particles.remove_if([currentTime](const Particle& particles)
		{
			return currentTime > particles.life;
		});
}

void Particles::ParticleRender(SDL_Renderer* renderer)
{
	// Render each particle to screen
	for (const auto& particle : particles)
	{
		SDL_Rect r;
		r.x = static_cast<int>(particle.x);
		r.y = static_cast<int>(particle.y);
		r.w = particleW;
		r.h = particleH;

		SDL_RenderCopy(renderer, particleTex, nullptr, &r);
	}
}

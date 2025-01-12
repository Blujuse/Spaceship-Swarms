#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <list>

struct Particle
{
	float x, y; // Position
	float velX, velY; // Velocity
	Uint32 life; // How long to last
};

class Particles
{
public:

	Particles(SDL_Renderer* renderer);

	virtual ~Particles();

	void ParticleStart(int spawnPosX, int spawnPosY);

	void ParticleUpdate();

	void ParticleRender(SDL_Renderer* renderer);

private:

	SDL_Texture* particleTex;

	int particleW, particleH;

	std::list<Particle> particles; // List of particles

	Uint32 emissionRate = 200;
	Uint32 emissionRange = 90;

	Uint32 lastParticleSpawnTime;
	Uint32 nextParticleSpawnTime;
};


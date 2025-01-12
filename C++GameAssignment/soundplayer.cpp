#include "soundplayer.h"
#include <iostream>

const int CHUNK_SIZE = 4096; // Number of frames passed to the mixer to play at a time

SoundPlayer::SoundPlayer()
{
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, CHUNK_SIZE) == -1)
	{
		std::cout << "Audio mixer could not be created\n";
		std::cout << SDL_GetError() << "\n";

		throw std::runtime_error("Mixer cannot start");
	}

	for (int i = 0; i < Sounds::TOTAL_SOUNDS; i++)
	{
		std::stringstream name;

		name << i;
		std::string path = "./Assets/Sounds/" + name.str() + ".wav";

		Mix_Chunk* sound = Mix_LoadWAV(path.c_str());

		soundFiles.push_back(sound);
	}
}

SoundPlayer::~SoundPlayer()
{
	for (auto& sound : soundFiles)
	{
		Mix_FreeChunk(sound);
	}

	if (backgroundMusic)
	{
		Mix_FreeMusic(backgroundMusic);
	}

	Mix_CloseAudio();
}

void SoundPlayer::PlaySound(Sounds sound)
{
	Mix_PlayChannel(-1, soundFiles[sound], 0);
}

void SoundPlayer::LoadBackgroundMusic(const std::string& filePath)
{
	backgroundMusic = Mix_LoadMUS(filePath.c_str());
	if (!backgroundMusic)
	{
		std::cout << "Failed to load background music: " << filePath << "\n";
		std::cout << Mix_GetError() << "\n";
		throw std::runtime_error("Background music loading failed");
	}
}

void SoundPlayer::PlayBackgroundMusic(bool loop)
{
	if (!backgroundMusic)
	{
		std::cout << "No background music loaded\n";
		return;
	}

	int loops = loop ? -1 : 1; // -1 for infinite loop
	if (Mix_PlayMusic(backgroundMusic, loops) == -1)
	{
		std::cout << "Failed to play background music\n";
		std::cout << Mix_GetError() << "\n";
	}
}

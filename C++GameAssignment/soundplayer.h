#pragma once

#include <SDL.h>
#include <SDL_mixer.h>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <algorithm>

enum Sounds
{
	SHOOT = 0,
	ASTEROID_BREAK,
	TOTAL_SOUNDS
};

class SoundPlayer
{
public:

	SoundPlayer();
	virtual ~SoundPlayer();

	void PlaySound(Sounds sound);

	void LoadBackgroundMusic(const std::string& filePath);

	void PlayBackgroundMusic(bool loop);

	void StopBackgroundMusic();

	void SetSoundVolume(int volume);

	void SetMusicVolume(int volume);

private:

	std::vector<Mix_Chunk*> soundFiles;

	Mix_Music* backgroundMusic = nullptr; // Pointer to background music
};


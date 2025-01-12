#pragma once

#include "soundplayer.h"

class BackgroundMusic
{
public:

	BackgroundMusic(int BGMNum);

	void LoopBGM();

	void BGMCleanup();

private:

	SoundPlayer* soundPlayer;
};


#include "backgroundmusic.h"

BackgroundMusic::BackgroundMusic(int BGMNum)
{
	soundPlayer = new SoundPlayer();

	if (BGMNum == 0)
	{
		soundPlayer->LoadBackgroundMusic("./Assets/Sounds/BGM.wav");
	}
	else if (BGMNum == 1)
	{
		soundPlayer->LoadBackgroundMusic("./Assets/Menu/MenuBGM.wav");
	}
}

void BackgroundMusic::LoopBGM()
{
	soundPlayer->PlayBackgroundMusic(true);
}

void BackgroundMusic::BGMCleanup()
{
	if (soundPlayer != nullptr)
	{
		delete soundPlayer;

		soundPlayer = nullptr;
	}
}

#pragma once

#include "player.h"

class MapBoundaries
{
public:

	void BoundariesInit();

	void BoundariesUpdate();

	void BoundariesClean();

private:

	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 640;

	const int PLAYER_WIDTH = 32;
	const int PLAYER_HEIGHT = 32;

	Player* playerChar;
};


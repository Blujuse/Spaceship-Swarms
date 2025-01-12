#pragma once

#include <SDL.h>
#include "init.h"
#include "gameloop.h"
#include "mainmenu.h"
#include "endmenu.h"

enum currentState
{
	MENU = 0,
	GAME,
	END,
	EXIT
};

class GameStateHandler
{
public:

	GameStateHandler();

	bool SDLInit();

	void CurrentGameState();

	void SetGameState(currentState setState);

	void SetGameState(int setState);

private:

	SDL_Window* window; // Using pointers to allow initialization after renderer creation
	SDL_Renderer* renderer;

	int state = MENU;
};
#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>

#include "fontrenderer.h"
#include "scoremanager.h"
#include "backgroundmusic.h"

class EndMenu
{
public:

	EndMenu(SDL_Renderer* mainRenderer, SDL_Window* mainWindow);
	~EndMenu();

	void MenuInitialise();

	void MenuUpdate();

	void ProcessInput();

	void MenuRender();

	int GameStateUpdate();

private:

	bool isRunning;
	int SET_GAME_STATE = 0;

	SDL_Renderer* renderer;
	SDL_Window* window;

	SDL_Surface* backgroundImg;
	SDL_Texture* backgroundTexture;

	SDL_Surface* logoImg;
	SDL_Texture* logoTexture;
	SDL_Rect logoRect = { 200, 100, 400, 100 };

	SDL_Surface* restartButtonImg;
	SDL_Texture* restartButtonTexture;
	SDL_Rect restartButtonRect = { 300, 400, 200, 50 };

	SDL_Surface* endButtonImg;
	SDL_Texture* endButtonTexture;
	SDL_Rect endButtonRect = { 300, 500, 200, 50 };

	BackgroundMusic* bgmPlayer;

	ScoreManager* scoreManager;
	std::unique_ptr<FontRenderer> fontRenderer;
};


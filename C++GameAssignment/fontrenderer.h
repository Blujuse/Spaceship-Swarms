#pragma once

#include <SDL_ttf.h>
#include <SDL.h>
#include <string>
#include <iostream>

class FontRenderer
{
public:

	FontRenderer(SDL_Renderer* sdlRenderer);

	void fontInit(int fontSize);

	void fontRender(const std::string& text, int xPos, int yPos);

	void fontClean();

private:

	SDL_Renderer* fontRenderer;
	TTF_Font* font;

	std::string fileLocation;
};


#include "fontrenderer.h"

FontRenderer::FontRenderer(SDL_Renderer* sdlRenderer)
{
	fontRenderer = sdlRenderer;
}

void FontRenderer::fontInit(int fontSize)
{
	// If a font is already loaded, close it
	if (font != NULL)
	{
		TTF_CloseFont(font);
		font = NULL;
	}

	// Initialize TTF if not already initialized
	int init = TTF_Init();
	if (init != 0)
	{
		std::cout << "TTF_Init error: " << SDL_GetError() << std::endl;
	}

	// Load the font with the specified size
	font = TTF_OpenFont("./Assets/Fonts/SpaceInvasion.ttf", fontSize);
	if (font == NULL)
	{
		std::cout << "TTF_OpenFont error: " << SDL_GetError() << std::endl;
	}
}

void FontRenderer::fontRender(const std::string& text, int xPos, int yPos)
{
	SDL_Color colour = SDL_Color();
	colour.r = 255; // Red
	colour.g = 255; // Green
	colour.b = 255; // Blue
	colour.a = 255; // Alpha

	// Creates an image representing the text that is input
	SDL_Surface* textImage = TTF_RenderText_Solid(font, text.c_str(), colour);

	// Once the image is made, render same way as the player
	SDL_Texture* texture = SDL_CreateTextureFromSurface(fontRenderer, textImage);

	// Used to place the image
	SDL_Rect destRect = { xPos, yPos, textImage->w, textImage->h };

	// Render to screen
	SDL_RenderCopy(fontRenderer, texture, NULL, &destRect);

	// Since the text has been rendered
	// Remove both to free memory
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(textImage);
}

void FontRenderer::fontClean()
{
	TTF_CloseFont(font);
}
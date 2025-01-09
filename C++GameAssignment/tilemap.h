#pragma once

#include <SDL.h>
#include <string>
#include "init.h"
#include <vector>

class Tilemap
{
public:

	Tilemap(SDL_Renderer* renderer) : renderer(renderer) {}

	void TilemapInit();

	void TilemapDraw();

	void TilemapClean();

	int IsValidIndex(int Offset, int Index, int Size);

public:

	// Used to draw the map
	std::vector<std::vector<int>> MAP_DATA = {
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	};


	//
	// OLD TILEMAP CODE
	//

	/* Constructor for tilemap
	 Parameters:
	 Image location, SDL_Renderer, Window width, Window height, Size of tile pixels
	*/
	//Tilemap(const std::string& tilePath, SDL_Renderer* renderer, int windowW, int windowH, int tilePixelSize);
	//~Tilemap();

	/* Renderer for tilemap
	 Parameters:
	 SDL_Renderer, Window width, Window height, Size of tile pixels
	*/
	//void RenderTilemap(SDL_Renderer* renderer, int windowW, int windowH, int tilePixelSize);

private:

	SDL_Renderer* renderer;

	SDL_Texture* tilemapTex;

	SDL_Rect selectT1;
	SDL_Rect selectT2;
	SDL_Rect selectT3;
	SDL_Rect selectT4;
	SDL_Rect selectT5;
	SDL_Rect selectT6;
	SDL_Rect selectT7;
	SDL_Rect selectT8;
	SDL_Rect selectT9;
	SDL_Rect selectT10;
	SDL_Rect selectT11;
	SDL_Rect selectT12;


	// Tilemap
	

	//
	// OLD TILEMAP CODE
	//

	//SDL_Surface* tilemapImg;
	
	// Creating arrays for tile map with a max of 0920 x 0080
	// Added ** to allow for 2D array and dynamic memory allocation, two types of memory static and dynamic
	// Below is dynamic
	//SDL_Rect** tile;
	//int** tilemapSize;
	
	// This would be static
	//int tilemapW, tilemapH;
};
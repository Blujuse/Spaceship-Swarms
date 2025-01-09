#include "tilemap.h"

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

void Tilemap::TilemapInit()
{
	SDL_Surface* surface = IMG_Load("./Assets/Tilemap/TilemapLarge.png"); // Gets the tilemap image
	this->tilemapTex = SDL_CreateTextureFromSurface(this->renderer, surface); // Creating texture
	SDL_FreeSurface(surface); // Get rid of the surface img, not needed anymore

	// Selecting tiles from tilemap { x, y, w, h }
	selectT1 = { 0,0,32,32 };
	selectT2 = { 32,0,32,32 };
	selectT3 = { 64,0,32,32 };
	selectT4 = { 96,0,32,32 };
	selectT5 = { 0,32,32,32 };
	selectT6 = { 32,32,32,32 };
	selectT7 = { 64,32,32,32 };
	selectT8 = { 96,32,32,32 };
	selectT9 = { 0,64,32,32 };
	selectT10 = { 32,64,32,32 };
	selectT11 = { 64,64,32,32 };
	selectT12 = { 96,64,32,32 };

}

void Tilemap::TilemapDraw()
{
	// For each row and collumn draw certain tiles
	for (int i = 0; i < MAP_DATA.size(); i++) {
		for (int j = 0; j < MAP_DATA[i].size(); j++) {
			SDL_Rect dest = { j * 32,i * 32,32,32 }; // Places them side by side correctly
			SDL_RenderCopy(renderer, tilemapTex, &selectT1, &dest); // Choose tile tile to place, 0 is tile 1
			if (MAP_DATA[i][j] == 1) {
				SDL_RenderCopy(renderer, tilemapTex, &selectT2, &dest); // Choose tile tile to place, 1 is tile 2
			}
		}
	}
}

void Tilemap::TilemapClean()
{
	SDL_DestroyTexture(tilemapTex); // Free up memory
}

//
// OLD TILEMAP CODE
//

/*
Tilemap::Tilemap(const std::string& tilePath, SDL_Renderer* renderer, int windowW, int windowH, int tilePixelSize)
	:tilemapW {}, tilemapH{}
{
	// Loading image and turning it into texture, then freeing image data that is not needed
	tilemapImg = IMG_Load(tilePath.c_str());
	tilemapTex = SDL_CreateTextureFromSurface(renderer, tilemapImg);
	SDL_FreeSurface(tilemapImg);

	// Scaling tilemap to window size based on what is entered in the paramaters for tilePixelSize
	tilemapW = windowW / tilePixelSize;
	tilemapH = windowH / tilePixelSize;

	// Using window width to set up first part of 2D array
	// Creating an array of pointers based on window width
	tilemapSize = new int*[tilemapW]; // Represnts the num of tiles 
	tile = new SDL_Rect*[tilemapW]; // Represents the tiles x, y, w, h

	// For each row in my array it will add another array for the height
	for (int i = 0; i < tilemapW; i++) 
	{
		tilemapSize[i] = new int[tilemapH];
		tile[i] = new SDL_Rect[tilemapH];
	}

	// Randomly placing tiles within the entire size of the tile map
	srand(static_cast<unsigned int>(time(NULL)));
	for (int x = 0; x < tilemapW; x++)
	{
		for (int y = 0; y < tilemapH; y++)
		{
			tilemapSize[x][y] = rand() % 4 + 1;
		}
	}

	// Placing tiles offset from oneanother
	for (int x = 0; x < tilemapW; x++)
	{
		for (int y = 0; y < tilemapH; y++)
		{
			tile[x][y].x = x * tilePixelSize;
			tile[x][y].y = y * tilePixelSize;
			tile[x][y].w = tilePixelSize;
			tile[x][y].h = tilePixelSize;
		}
	}

	// Selecting tiles from tilemap { x, y, w, h }
	selectT1 = { 0,0,tilePixelSize,tilePixelSize };
	selectT2 = { tilePixelSize,0,tilePixelSize,tilePixelSize };
	selectT3 = { 0,tilePixelSize,tilePixelSize,tilePixelSize };
	selectT4 = { tilePixelSize,tilePixelSize,tilePixelSize,tilePixelSize };
}

// Destroying not needed things after window is closed
Tilemap::~Tilemap()
{
	SDL_DestroyTexture(tilemapTex);

	// Release dynamic memory as it is now managed manually
	for (int i = 0; i < tilemapW; i++)
	{
		delete[] tile[i];
		delete[] tilemapSize[i];
	}

	delete[] tile;
	delete[] tilemapSize;
}

void Tilemap::RenderTilemap(SDL_Renderer* renderer, int windowW, int windowH, int tilePixelSize)
{
	// Making sure the tilemap is correct size
	tilemapW = windowW / tilePixelSize;
	tilemapH = windowH / tilePixelSize;

	// Making sure this is set correctly
	tile[tilemapW][tilemapH];

	// Placing the tiles along allocated points in the array and choosing which ones to place
	for (int x = 0; x < tilemapW; x++)
	{
		for (int y = 0; y < tilemapH; y++)
		{
			switch (tilemapSize[x][y])
			{
			case 1:
				SDL_RenderCopy(renderer, tilemapTex, &selectT1, &tile[x][y]);
				break;
			case 2:
				SDL_RenderCopy(renderer, tilemapTex, &selectT2, &tile[x][y]);
				break;
			case 3:
				SDL_RenderCopy(renderer, tilemapTex, &selectT3, &tile[x][y]);
				break;
			case 4:
				SDL_RenderCopy(renderer, tilemapTex, &selectT4, &tile[x][y]);
				break;
			}
		}
	}
}
*/
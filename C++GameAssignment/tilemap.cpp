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

	LoadTilemapFromFile();
}

void Tilemap::LoadTilemapFromFile()
{
	//
	// WHEN MAKING MAP FOR FIRST TIME REPLACE THE BELOW READ WITH THE CODE BELOW IT
	// THIS FIXES ISSUES OF READING AND WRITING 
	//
	// Open the tilemap file for reading as text
	std::ifstream tilemap_stream("./Assets/Tilemap/SpaceMap.txt", std::ios::binary);

	//std::ifstream tilemap_stream("./Assets/Tilemap/SpaceMap.txt");

	// Check if file was opened ok
	if (!tilemap_stream.is_open())
	{
		std::cout << "Failed to open map\n";

		return;
	}

	// Read through each row of the file
	for (int rowIdx = 0; rowIdx < MAP_DATA.size(); rowIdx++)
	{
		// Read through each collum of the file
		for (int colIdx = 0; colIdx < MAP_DATA[rowIdx].size(); colIdx++)
		{
			//
			// WHEN MAKING MAP FOR FIRST TIME REPLACE THE BELOW READ WITH THE CODE BELOW IT
			// THIS FIXES ISSUES OF READING AND WRITING 
			//
			tilemap_stream.read(reinterpret_cast<char*>(&MAP_DATA[rowIdx][colIdx]), sizeof(int));

			
			//// Variable to store the value read from the file
			//std::string tilevalue;

			//// Read from the file into the string variable
			//tilemap_stream >> tilevalue;

			//// Convert to an integer
			//int value = atoi(tilevalue.c_str());

			//// Add the value to the row vector
			//MAP_DATA[rowIdx][colIdx] = value;
		}
	}

	tilemap_stream.close();
}

void Tilemap::saveTilemapToFile()
{
	// Open the tilemap file for writing as text
	std::ofstream tilemap_stream("./Assets/Tilemap/SpaceMap.txt", std::ios::binary);

	// Check if the file was opened ok
	if (!tilemap_stream.is_open())
	{
		std::cout << "Failed to open!\n";

		return;
	}

	// Now write the MAP_DATA contents to a file
	// Loop through each row of the file
	for (int rowIdx = 0; rowIdx < MAP_DATA.size(); rowIdx++)
	{
		for (int colIdx = 0; colIdx < MAP_DATA[rowIdx].size(); colIdx++)
		{
			tilemap_stream.write(reinterpret_cast<char*>(&MAP_DATA[rowIdx][colIdx]), sizeof(int));
		}
	}

	tilemap_stream.close();
}

void Tilemap::TilemapDraw()
{
	// For each row and collumn draw certain tiles
	for (int i = 0; i < MAP_DATA.size(); i++) 
	{
		for (int j = 0; j < MAP_DATA[i].size(); j++) 
		{
			SDL_Rect dest = { j * 32,i * 32,32,32 }; // Places them side by side correctly

			SDL_RenderCopy(renderer, tilemapTex, &selectT1, &dest); // Choose tile tile to place, 0 is tile 1

			if (MAP_DATA[i][j] == 1) 
			{
				SDL_RenderCopy(renderer, tilemapTex, &selectT2, &dest); // Choose tile tile to place, 1 is tile 2
			}

			if (MAP_DATA[i][j] == 2)
			{
				SDL_RenderCopy(renderer, tilemapTex, &selectT3, &dest); // Choose tile tile to place, 1 is tile 2
			}

			if (MAP_DATA[i][j] == 3)
			{
				SDL_RenderCopy(renderer, tilemapTex, &selectT4, &dest); // Choose tile tile to place, 1 is tile 2
			}

			if (MAP_DATA[i][j] == 4)
			{
				SDL_RenderCopy(renderer, tilemapTex, &selectT5, &dest); // Choose tile tile to place, 1 is tile 2
			}

			if (MAP_DATA[i][j] == 5)
			{
				SDL_RenderCopy(renderer, tilemapTex, &selectT6, &dest); // Choose tile tile to place, 1 is tile 2
			}

			if (MAP_DATA[i][j] == 6)
			{
				SDL_RenderCopy(renderer, tilemapTex, &selectT7, &dest); // Choose tile tile to place, 1 is tile 2
			}

			if (MAP_DATA[i][j] == 7)
			{
				SDL_RenderCopy(renderer, tilemapTex, &selectT8, &dest); // Choose tile tile to place, 1 is tile 2
			}

			if (MAP_DATA[i][j] == 8)
			{
				SDL_RenderCopy(renderer, tilemapTex, &selectT9, &dest); // Choose tile tile to place, 1 is tile 2
			}

			if (MAP_DATA[i][j] == 9)
			{
				SDL_RenderCopy(renderer, tilemapTex, &selectT10, &dest); // Choose tile tile to place, 1 is tile 2
			}

			if (MAP_DATA[i][j] == 10)
			{
				SDL_RenderCopy(renderer, tilemapTex, &selectT11, &dest); // Choose tile tile to place, 1 is tile 2
			}

			if (MAP_DATA[i][j] == 11)
			{
				SDL_RenderCopy(renderer, tilemapTex, &selectT12, &dest); // Choose tile tile to place, 1 is tile 2
			}
		}
	}
}

void Tilemap::TilemapClean()
{
	SDL_DestroyTexture(tilemapTex); // Free up memory
}
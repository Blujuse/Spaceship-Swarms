#include "init.h"

#include <iostream>
#include <SDL.h>

int initializeSDL()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "Something went wrong! " << SDL_GetError() << "\n";
        return -1;
    }
    
    return(0);
}

int createWindow(SDL_Window*& window, const char* name, int windowWidth, int windowHeight)
{
    window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    
    if (window == nullptr) // If the window cannot be created this text will be displayed within the console and the window will close
    {
        std::cout << "Something went wrong creating window! " << SDL_GetError() << "\n";

        return -2;
    }

    return(0);
}

int createRenderer(SDL_Window* window ,SDL_Renderer*& renderer)
{
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer) // If there is no renderer it will make one, usually only done once and is during the program initialisation
    {
        std::cout << "Error creating renderer: " << SDL_GetError() << std::endl; // Similar to other SDL functions check if the renderer was made correctly
        return false;
    }

    return(0);
}
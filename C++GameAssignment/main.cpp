// C++GameAssignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define SDL_MAIN_HANDLED
#include <iostream>
#include "gamestatehandler.h"
#include "gameloop.h"

int main()
{
    // Decide the window width and height
    //GameLoop game(800, 640);

    GameStateHandler gameHandler;

    // Calls the initialize functions & checks if it's has been completed successfully
    if (!gameHandler.SDLInit())
    {
        // If not display this message
        std::cerr << "Failed to initialize the game." << std::endl;
        return -1;
    }

    // Run the game
    //game.update();

    gameHandler.CurrentGameState();

    return 0;
}
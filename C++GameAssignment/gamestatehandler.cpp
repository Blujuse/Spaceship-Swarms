#include "gamestatehandler.h"

GameStateHandler::GameStateHandler() : window(nullptr), renderer(nullptr) {}

bool GameStateHandler::SDLInit()
{
    // Initialize SDL
    initializeSDL();

    // Create the window with the params made in constructor
    createWindow(window, "Spaceship Shooters", 800, 640);

    // Create a renderer for the window
    createRenderer(window, renderer);

    return true;
}

void GameStateHandler::CurrentGameState()
{
    while (state != EXIT)
    {
        //std::cout << "Current State: " << state << std::endl;

        switch (state)
        {

            case MENU: 
            { 
                //std::cout << "In Menu, State: " << state << std::endl;

                MainMenu* mainMenu = new MainMenu(this->renderer, this->window);

                mainMenu->MenuInitialise();

                mainMenu->MenuUpdate();

                state = mainMenu->GameStateUpdate();

                delete mainMenu;

                // TEMPORARY
                //SetGameState(GAME);
            }
                break;

            case GAME:
            {
                //std::cout << "In Game, State: " << state << std::endl;

                GameLoop* game = new GameLoop(800, 640); // Construct

                game->initialize(this->renderer, this->window); // Initialise stuff

                game->update(); // Update the game

                state = game->GameStateUpdate(); // Update state

                game->cleanUp(); // Remove stuff from memory
            }
                break;

            case END:
            {
                //std::cout << "In End, State: " << state << std::endl;

                EndMenu* endMenu = new EndMenu(this->renderer, this->window);

                endMenu->MenuInitialise();

                endMenu->MenuUpdate();

                state = endMenu->GameStateUpdate();

                delete endMenu;
            }
                break;

            case EXIT:
            {
                //std::cout << "In Exit, State: " << state << std::endl;

                SDL_DestroyWindow(window);
                SDL_DestroyRenderer(renderer);
                SDL_Quit();
            }
                break;
        }
    }
}

void GameStateHandler::SetGameState(currentState setState)
{
    state = setState;
}

// Contains main functions for game
#include "gameloop.h"
#include <iostream>

// GameLoop Constructor and Variable Declaration
GameLoop::GameLoop(int width, int height)
    : window(nullptr), renderer(nullptr), isRunning(true),
    windowWidth(width), windowHeight(height), 
    playerCharacter(nullptr), tilemap(nullptr),
    bullets(nullptr), enemies(nullptr) {}

// GameLoop Destructor
GameLoop::~GameLoop() 
{
    cleanUp();
}

// Contains code to setup; SDL, Window, Renderer, Player, Tilemap
bool GameLoop::initialize() 
{
    // Initialize SDL
    initializeSDL();

    // Create the window with the params made in constructor
    createWindow(window, "C++ Game", windowWidth, windowHeight);

    // Create a renderer for the window
    createRenderer(window, renderer);

    // Create Player
    playerCharacter = new Player("./Assets/Player/Placeholder.png", renderer);
    playerCharacter->setPosition(windowWidth / 2, windowHeight / 2);

    // Create Tilemap
    //tilemap = new Tilemap("./Assets/Tilemap/TilemapTest.png", renderer, windowWidth, windowHeight, 32);
    tilemap = new Tilemap(this->renderer);
    tilemap->TilemapInit();

    // Create Bullets
    bullets = new BulletManager(this->renderer, this->playerCharacter);
    bullets->BulletInit();

    // Create Enemies
    enemies = new EnemiesManager(this->renderer, this->bullets);
    enemies->EnemiesInit();

    // New Enemies
    enemiesTwo = new EnemiesMovement(this->renderer, tilemap, playerCharacter);
    enemiesTwo->EnemiesInit();

    return true;
}

void GameLoop::update() 
{
    // Game will always run until the window is closed
    while (isRunning) 
    {
        processInput();

        bullets->BulletUpdate();

        enemies->EnemiesUpdate();

        enemiesTwo->EnemiesUpdate();

        mapBounds->BoundariesUpdate();

        // PLAYER POSITION DEBUGGING
        //int posX;
        //posX = playerCharacter->getPosX();
        //std::cout << "Pos X : " << posX << std::endl;

        render();

        SDL_Delay(17); // Used to limit the framerate to 60 FPS
    }
}

void GameLoop::processInput() 
{
    SDL_Event evt;
    while (SDL_PollEvent(&evt)) 
    {
        // Close out the app by turning isRunning to false
        if (evt.type == SDL_QUIT) 
        {
            isRunning = false;
        }
    }

    // Move towards player
    enemiesTwo->MoveToPlayer();

    // Creating a local keystate variable to feed to the handleInput function
    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    playerCharacter->handleInput(keystate);

    // Takes keystate to handle bullet input
    bullets->BulletInput(keystate);
}

void GameLoop::render() 
{
    // Clearing the renderer before each frame to prevent 'ghosting' effect
    SDL_RenderClear(renderer);

    // Tells the specific player & tilemap to render
    //tilemap->RenderTilemap(renderer, windowWidth, windowHeight, 32);
    tilemap->TilemapDraw();
    playerCharacter->render(renderer);

    // Draw bullets
    bullets->BulletDraw();

    // Draw enemies
    enemies->EnemiesDraw();

    // Draw enemies new
    enemiesTwo->EnemiesDraw();

    // Show it off to the renderer
    SDL_RenderPresent(renderer);
}

void GameLoop::cleanUp() 
{
    // Delete will remove anything which was allocated to the heap using 'new', this frees up memory
    delete playerCharacter;

    tilemap->TilemapClean();
    delete tilemap;
    
    // Clean up bullet stuff
    bullets->BulletClean();
    delete bullets;

    // Clean up enemies stuff
    enemies->EnemiesClean();
    delete enemies;

    enemiesTwo->EnemiesClean();
    delete enemiesTwo;

    // Destroy the renderer & window to free up memory
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
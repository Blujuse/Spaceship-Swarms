// Contains main functions for game
#include "gameloop.h"
#include <iostream>

// GameLoop Constructor and Variable Declaration
GameLoop::GameLoop(int width, int height)
    : isRunning(true), windowWidth(width), windowHeight(height), 
    playerCharacter(nullptr), tilemap(nullptr), bullets(nullptr), 
    enemies(nullptr), bgmPlayer(nullptr), holdingRenderer(nullptr),
    holdingWindow(nullptr), trackingEnemyOne(nullptr), trackingEnemyTwo(nullptr),
    trackingEnemyThree(nullptr), trackingEnemyFour(nullptr) {}

// GameLoop Destructor
GameLoop::~GameLoop() 
{
    cleanUp();
}

// Contains code to setup; SDL, Window, Renderer, Player, Tilemap
bool GameLoop::initialize(SDL_Renderer* renderer, SDL_Window* window) 
{
    // Initialize SDL
    //initializeSDL();

    // Create the window with the params made in constructor
    //createWindow(window, "C++ Game", windowWidth, windowHeight);

    // Create a renderer for the window
    //createRenderer(window, renderer);

    // Create Tilemap
    //tilemap = new Tilemap("./Assets/Tilemap/TilemapTest.png", renderer, windowWidth, windowHeight, 32);
    holdingRenderer = renderer;
    holdingWindow = window;

    tilemap = new Tilemap(renderer);
    tilemap->TilemapInit();

    // Create Player
    playerCharacter = new Player("./Assets/Player/Spaceship.png", renderer);
    playerCharacter->setPosition(windowWidth / 2, windowHeight / 2);

    // Create Bullets
    bullets = new BulletManager(renderer, this->playerCharacter);
    bullets->BulletInit();

    // Create Enemies
    enemies = new EnemiesManager(renderer, this->bullets);
    enemies->EnemiesInit();

    // Tracking Enemies
    trackingEnemyOne = new EnemiesMovement(renderer, tilemap, playerCharacter);
    trackingEnemyOne->EnemiesInit( 1, 1 );
    trackingEnemyTwo = new EnemiesMovement(renderer, tilemap, playerCharacter);
    trackingEnemyTwo->EnemiesInit( 23, 1 );
    trackingEnemyThree = new EnemiesMovement(renderer, tilemap, playerCharacter);
    trackingEnemyThree->EnemiesInit(1, 18);
    trackingEnemyFour = new EnemiesMovement(renderer, tilemap, playerCharacter);
    trackingEnemyFour->EnemiesInit(23, 18);

    // Setting up font and font size
    fontRenderer = std::unique_ptr<FontRenderer>(new FontRenderer(renderer));
    fontRenderer->fontInit(46);

    // Create an instance so it is not nullptr
    scoreManager = new ScoreManager();
    scoreManager->SetScore(0);

    // Create bgm
    bgmPlayer = new BackgroundMusic(0);
    bgmPlayer->LoopBGM();

    //std::cout << "High Score: " << scoreManager->GetHighScore() << std::endl;
    scoreManager->GetHighScore();

    return true;
}

void GameLoop::update() 
{
    // Game will always run until the window is closed
    while (isRunning) 
    {
        processInput();

        bullets->BulletUpdate();

        // Use scoreManager in enemies update so score can be added
        enemies->EnemiesUpdate(scoreManager);

        // Moving enemies
        trackingEnemyOne->EnemiesUpdate();
        trackingEnemyTwo->EnemiesUpdate();
        trackingEnemyThree->EnemiesUpdate();
        trackingEnemyFour->EnemiesUpdate();

        // PLAYER POSITION DEBUGGING
        //int posX;
        //posX = playerCharacter->getPosX();
        //std::cout << "Pos X : " << posX << std::endl;

        UpdateTilemap();

        render();

        if (trackingEnemyOne->GameStateUpdate() == 2)
        {
            SET_GAME_STATE = 2;
        }

        if (trackingEnemyTwo->GameStateUpdate() == 2)
        {
            SET_GAME_STATE = 2;
        }

        if (trackingEnemyThree->GameStateUpdate() == 2)
        {
            SET_GAME_STATE = 2;
        }

        if (trackingEnemyFour->GameStateUpdate() == 2)
        {
            SET_GAME_STATE = 2;
        }

        SDL_Delay(17); // Used to limit the framerate to 60 FPS
    }
}

void GameLoop::processInput() 
{
    SDL_Event evt;
    while (SDL_PollEvent(&evt)) 
    {
        // Close out the app by turning isRunning to false
        if (evt.type == SDL_QUIT || triggerSceneChange == true) // FOR SOME REASON THIS IS THE WAY I HAVE TO CHANGE SCENE WHEN "KILLED"
        {
            isRunning = false;
            SET_GAME_STATE = 3; // THIS CHANGES "SCENE"
        }

        if (SET_GAME_STATE == 2)
        {
            triggerSceneChange = true; // THIS GETS SET TO TRUE WHEN ENEMIES OVERLAP WITH PLAYER  
        }
    }

    // Move towards player
    trackingEnemyOne->MoveToPlayer();
    trackingEnemyTwo->MoveToPlayer();
    trackingEnemyThree->MoveToPlayer();
    trackingEnemyFour->MoveToPlayer();

    // Creating a local keystate variable to feed to the handleInput function
    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    playerCharacter->handleInput(keystate);

    // Takes keystate to handle bullet input
    bullets->BulletInput(keystate);
}

void GameLoop::render() 
{
    // Clearing the renderer before each frame to prevent 'ghosting' effect
    SDL_RenderClear(holdingRenderer);

    // Tells the specific player & tilemap to render
    //tilemap->RenderTilemap(renderer, windowWidth, windowHeight, 32);
    tilemap->TilemapDraw();
    playerCharacter->render(holdingRenderer);

    // Draw bullets
    bullets->BulletDraw();

    // Draw asteroids
    enemies->EnemiesDraw();

    // Draw moving enemies
    trackingEnemyOne->EnemiesDraw();
    trackingEnemyTwo->EnemiesDraw();
    trackingEnemyThree->EnemiesDraw();
    trackingEnemyFour->EnemiesDraw();

    // Draw the score on the screen
    fontRenderer->fontRender("SCORE: " + std::to_string(scoreManager->GetScore()), 10, 10);

    // Show it off to the renderer
    SDL_RenderPresent(holdingRenderer);
}

void GameLoop::cleanUp() 
{
    // Save tilemap to file
    //tilemap->saveTilemapToFile();

    // Save high score to file
    scoreManager->SaveHighScoreToFile("./Assets/Player/HighScore.txt");

    // Delete will remove anything which was allocated to the heap using 'new', this frees up memory
    delete playerCharacter;

    //tilemap->saveTilemapToFile();
    tilemap->TilemapClean();
    delete tilemap;
    
    // Clean up bullet stuff
    bullets->BulletClean();
    delete bullets;

    // Clean up asteroids stuff
    enemies->EnemiesClean();
    delete enemies;

    // Clean up moving enemies
    trackingEnemyOne->EnemiesClean();
    delete trackingEnemyOne;
    trackingEnemyTwo->EnemiesClean();
    delete trackingEnemyTwo;
    trackingEnemyThree->EnemiesClean();
    delete trackingEnemyThree;
    trackingEnemyFour->EnemiesClean();
    delete trackingEnemyFour;

    // Clean up font
    fontRenderer->fontClean();

    // Clean up score stuff
    scoreManager = nullptr;

    // Clean BGM
    bgmPlayer->BGMCleanup();

    // Destroy the renderer & window to free up memory
    //SDL_DestroyRenderer(holdingRenderer);
    //SDL_DestroyWindow(holdingWindow);
}

// USED TO SEND THE CHANGE OF STATE TO GAME HANDLER
int GameLoop::GameStateUpdate()
{
    return SET_GAME_STATE;
}

//
// HARDCODED TILEMAP UPDATER
// Hardcoded due to time constraints and quick implamentation
//
void GameLoop::UpdateTilemap()
{
    //
    // UPDATING POWER UPS ONE
    //
    if (trackingEnemyOne->ReturnPlayerTileX() == 12 && trackingEnemyOne->ReturnPlayerTileY() == 7 || 
        trackingEnemyOne->ReturnPlayerTileX() == 12 && trackingEnemyOne->ReturnPlayerTileY() == 8 || 
        trackingEnemyOne->ReturnPlayerTileX() == 12 && trackingEnemyOne->ReturnPlayerTileY() == 9 ||
        trackingEnemyOne->ReturnPlayerTileX() == 11 && trackingEnemyOne->ReturnPlayerTileY() == 8 ||
        trackingEnemyOne->ReturnPlayerTileX() == 13 && trackingEnemyOne->ReturnPlayerTileY() == 8)
    {
        if (!tileChangeTriggeredPowerupOne)
        {
            tileChangeTriggeredPowerupOne = true;
            tileChangeReturnTimePowerupOne = SDL_GetTicks(); // Record the time

            tilemap->MAP_DATA[8][12] = 2;

            bullets->DecreaseBulletTimer(25); // Decreasing time to shoot
        }
    }

    // Check if the timer has ended to revert the tiles
    if (tileChangeTriggeredPowerupOne && SDL_GetTicks() - tileChangeReturnTimePowerupOne >= 10000) // Ten seconds
    {
        // Revert tiles back to original
        tilemap->MAP_DATA[8][12] = 3;

        // Reset the tile change trigger
        tileChangeTriggeredPowerupOne = false;
        tileChangeReturnTimePowerupOne = 0;
    }

    //
    // UPDATING POWER UPS TWO
    //
    if (trackingEnemyOne->ReturnPlayerTileX() == 3 && trackingEnemyOne->ReturnPlayerTileY() == 3 ||
        trackingEnemyOne->ReturnPlayerTileX() == 3 && trackingEnemyOne->ReturnPlayerTileY() == 4 ||
        trackingEnemyOne->ReturnPlayerTileX() == 3 && trackingEnemyOne->ReturnPlayerTileY() == 5 ||
        trackingEnemyOne->ReturnPlayerTileX() == 4 && trackingEnemyOne->ReturnPlayerTileY() == 4 ||
        trackingEnemyOne->ReturnPlayerTileX() == 5 && trackingEnemyOne->ReturnPlayerTileY() == 4)
    {
        if (!tileChangeTriggeredPowerupTwo)
        {
            tileChangeTriggeredPowerupTwo = true;
            tileChangeReturnTimePowerupTwo = SDL_GetTicks(); // Record the time

            tilemap->MAP_DATA[4][3] = 2;

            bullets->DecreaseBulletTimer(25); // Decreasing time to shoot

        }
    }

    // Check if the timer has ended to revert the tiles
    if (tileChangeTriggeredPowerupTwo && SDL_GetTicks() - tileChangeReturnTimePowerupTwo >= 10000) // Ten seconds
    {
        // Revert tiles back to original
        tilemap->MAP_DATA[4][3] = 3;

        // Reset the tile change trigger
        tileChangeTriggeredPowerupTwo = false;
        tileChangeReturnTimePowerupTwo = 0;
    }

    //
    // UPDATING POWER UPS THREE
    //
    if (trackingEnemyOne->ReturnPlayerTileX() == 20 && trackingEnemyOne->ReturnPlayerTileY() == 9 ||
        trackingEnemyOne->ReturnPlayerTileX() == 20 && trackingEnemyOne->ReturnPlayerTileY() == 10 ||
        trackingEnemyOne->ReturnPlayerTileX() == 20 && trackingEnemyOne->ReturnPlayerTileY() == 11 ||
        trackingEnemyOne->ReturnPlayerTileX() == 19 && trackingEnemyOne->ReturnPlayerTileY() == 10 ||
        trackingEnemyOne->ReturnPlayerTileX() == 21 && trackingEnemyOne->ReturnPlayerTileY() == 10)
    {
        if (!tileChangeTriggeredPowerupThree)
        {
            tileChangeTriggeredPowerupThree = true;
            tileChangeReturnTimePowerupThree = SDL_GetTicks(); // Record the time

            tilemap->MAP_DATA[10][20] = 2;

            bullets->DecreaseBulletTimer(25); // Decreasing time to shoot

        }
    }

    // Check if the timer has ended to revert the tiles
    if (tileChangeTriggeredPowerupThree && SDL_GetTicks() - tileChangeReturnTimePowerupThree >= 10000) // Ten seconds
    {
        // Revert tiles back to original
        tilemap->MAP_DATA[10][20] = 3;

        // Reset the tile change trigger
        tileChangeTriggeredPowerupThree = false;
        tileChangeReturnTimePowerupThree = 0;
    }

    //
    // UPDATING POWER UPS FOUR
    //
    if (trackingEnemyOne->ReturnPlayerTileX() == 6 && trackingEnemyOne->ReturnPlayerTileY() == 16 ||
        trackingEnemyOne->ReturnPlayerTileX() == 6 && trackingEnemyOne->ReturnPlayerTileY() == 17 ||
        trackingEnemyOne->ReturnPlayerTileX() == 6 && trackingEnemyOne->ReturnPlayerTileY() == 18 ||
        trackingEnemyOne->ReturnPlayerTileX() == 5 && trackingEnemyOne->ReturnPlayerTileY() == 17 ||
        trackingEnemyOne->ReturnPlayerTileX() == 7 && trackingEnemyOne->ReturnPlayerTileY() == 17)
    {
        if (!tileChangeTriggeredPowerupFour)
        {
            tileChangeTriggeredPowerupFour = true;
            tileChangeReturnTimePowerupFour = SDL_GetTicks(); // Record the time

            tilemap->MAP_DATA[17][6] = 2;

            bullets->DecreaseBulletTimer(25); // Decreasing time to shoot
        }
    }

    // Check if the timer has ended to revert the tiles
    if (tileChangeTriggeredPowerupFour && SDL_GetTicks() - tileChangeReturnTimePowerupFour >= 10000) // Ten seconds
    {
        // Revert tiles back to original
        tilemap->MAP_DATA[17][6] = 3;

        // Reset the tile change trigger
        tileChangeTriggeredPowerupFour = false;
        tileChangeReturnTimePowerupFour = 0;
    }

    //
    // TRACKING FIRST PLANET TILES
    // 
    // Check for the specific conditions to trigger the tile change
    if (trackingEnemyOne->ReturnPlayerTileX() == 18 && trackingEnemyOne->ReturnPlayerTileY() == 3 ||
        trackingEnemyOne->ReturnPlayerTileX() == 18 && trackingEnemyOne->ReturnPlayerTileY() == 4 ||
        trackingEnemyOne->ReturnPlayerTileX() == 19 && trackingEnemyOne->ReturnPlayerTileY() == 3 ||
        trackingEnemyOne->ReturnPlayerTileX() == 19 && trackingEnemyOne->ReturnPlayerTileY() == 4)
    {
        if (!tileChangeTriggeredOne)
        {
            tileChangeTriggeredOne = true;
            tileChangeStartTimeOne = SDL_GetTicks(); // Record the time
        }
    }
    else
    {
        tileChangeTriggeredOne = false;
    }

    // Check if the timer has ended
    if (tileChangeTriggeredOne && SDL_GetTicks() - tileChangeStartTimeOne >= 2000)
    {
        tilemap->MAP_DATA[3][18] = 2;
        tilemap->MAP_DATA[4][18] = 1;
        tilemap->MAP_DATA[3][19] = 0;
        tilemap->MAP_DATA[4][19] = 2;

        // Reset the trigger
        tileChangeTriggeredOne = false;
        tileChangeStartTimeOne = 0;
    }

    //
    // TRACKING SECOND PLANET TILES
    // 
    // Check for the specific conditions to trigger the tile change
    if (trackingEnemyOne->ReturnPlayerTileX() == 5 && trackingEnemyOne->ReturnPlayerTileY() == 10 ||
        trackingEnemyOne->ReturnPlayerTileX() == 6 && trackingEnemyOne->ReturnPlayerTileY() == 11 ||
        trackingEnemyOne->ReturnPlayerTileX() == 6 && trackingEnemyOne->ReturnPlayerTileY() == 10 ||
        trackingEnemyOne->ReturnPlayerTileX() == 5 && trackingEnemyOne->ReturnPlayerTileY() == 11)
    {
        if (!tileChangeTriggeredTwo)
        {
            tileChangeTriggeredTwo = true;
            tileChangeStartTimeTwo = SDL_GetTicks(); // Record the time
        }
    }
    else
    {
        tileChangeTriggeredTwo = false;
    }

    // Check if the timer has ended
    if (tileChangeTriggeredTwo && SDL_GetTicks() - tileChangeStartTimeTwo >= 2000)
    {
        tilemap->MAP_DATA[10][5] = 2;
        tilemap->MAP_DATA[11][5] = 1;
        tilemap->MAP_DATA[10][6] = 0;
        tilemap->MAP_DATA[11][6] = 2;

        // Reset the trigger
        tileChangeTriggeredTwo = false;
        tileChangeStartTimeTwo = 0;
    }

    //
    // TRACKING THIRD PLANET TILES
    // 
    // Check for the specific conditions to trigger the tile change
    if (trackingEnemyOne->ReturnPlayerTileX() == 11 && trackingEnemyOne->ReturnPlayerTileY() == 16 ||
        trackingEnemyOne->ReturnPlayerTileX() == 12 && trackingEnemyOne->ReturnPlayerTileY() == 16 ||
        trackingEnemyOne->ReturnPlayerTileX() == 11 && trackingEnemyOne->ReturnPlayerTileY() == 17 ||
        trackingEnemyOne->ReturnPlayerTileX() == 12 && trackingEnemyOne->ReturnPlayerTileY() == 17)
    {
        if (!tileChangeTriggeredThree)
        {
            tileChangeTriggeredThree = true;
            tileChangeStartTimeThree = SDL_GetTicks(); // Record the time
        }
    }
    else
    {
        tileChangeTriggeredThree = false;
    }

    // Check if the timer has ended
    if (tileChangeTriggeredThree && SDL_GetTicks() - tileChangeStartTimeThree >= 2000)
    {
        tilemap->MAP_DATA[16][11] = 2;
        tilemap->MAP_DATA[16][12] = 1;
        tilemap->MAP_DATA[17][11] = 0;
        tilemap->MAP_DATA[17][12] = 2;

        // Reset the trigger
        tileChangeTriggeredThree = false;
        tileChangeStartTimeThree = 0;
    }

    //std::cout << "X POS: " << trackingEnemyOne->ReturnPlayerTileX() << " Y POS: " << trackingEnemyOne->ReturnPlayerTileY() << std::endl;
}

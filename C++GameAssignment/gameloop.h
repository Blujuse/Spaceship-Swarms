// Contains variables for gameloop
#ifndef GAMELOOP_H
#define GAMELOOP_H

// Include anything needed in the gameloop cpp file here
#include <SDL.h>
#include "gamestatehandler.h"
#include "init.h"
#include "player.h"
#include "tilemap.h"
#include "bulletmanager.h"
#include "enemiesmanager.h"
#include "enemiesmovement.h"
#include "fontrenderer.h"
#include "scoremanager.h"
#include "backgroundmusic.h"

// Making new class called GameLoop
class GameLoop 
{
public:
    GameLoop(int width, int height);
    ~GameLoop();

    bool initialize(SDL_Renderer* renderer, SDL_Window* window);
    void update();
    void cleanUp();

    int GameStateUpdate(); // Used to update menus

    void UpdateTilemap();

private:
    void processInput();
    void render();

    bool triggerSceneChange = false;
    int SET_GAME_STATE = 1;
    bool isRunning;

    SDL_Renderer* holdingRenderer;
    SDL_Window* holdingWindow;
    int windowWidth;
    int windowHeight;

    Player* playerCharacter; // Using pointers to allow initialization after renderer creation
    Tilemap* tilemap;
    BulletManager* bullets;
    EnemiesManager* enemies;

    EnemiesMovement* trackingEnemyOne;
    EnemiesMovement* trackingEnemyTwo;
    EnemiesMovement* trackingEnemyThree;
    EnemiesMovement* trackingEnemyFour;

    std::unique_ptr<FontRenderer> fontRenderer;

    ScoreManager* scoreManager = nullptr;

    BackgroundMusic* bgmPlayer;

    // Used for changing big planets
    Uint32 tileChangeStartTimeOne = 0;
    bool tileChangeTriggeredOne = false;
    Uint32 tileChangeStartTimeTwo = 0;
    bool tileChangeTriggeredTwo = false; 
    Uint32 tileChangeStartTimeThree = 0;
    bool tileChangeTriggeredThree = false;

    // Used for changing powerups
    Uint32 tileChangeReturnTimePowerupOne = 0;
    bool tileChangeTriggeredPowerupOne = false;
    Uint32 tileChangeReturnTimePowerupTwo = 0;
    bool tileChangeTriggeredPowerupTwo = false;
    Uint32 tileChangeReturnTimePowerupThree = 0;
    bool tileChangeTriggeredPowerupThree = false;
    Uint32 tileChangeReturnTimePowerupFour = 0;
    bool tileChangeTriggeredPowerupFour = false;
};

#endif // GAMELOOP_H
// Contains variables for gameloop
#ifndef GAMELOOP_H
#define GAMELOOP_H

// Include anything needed in the gameloop cpp file here
#include <SDL.h>
#include "init.h"
#include "player.h"
#include "tilemap.h"
#include "bulletmanager.h"
#include "enemiesmanager.h"
#include "enemiesmovement.h"
#include "mapboundaries.h"

// Making new class called GameLoop
class GameLoop 
{
public:
    GameLoop(int width, int height);
    ~GameLoop();

    bool initialize();
    void update();
    void cleanUp();

private:
    void processInput();
    void render();

    SDL_Window* window; // Using pointers to allow initialization after renderer creation
    SDL_Renderer* renderer;
    bool isRunning;

    int windowWidth;
    int windowHeight;

    Player* playerCharacter; // Using pointers to allow initialization after renderer creation
    Tilemap* tilemap;
    BulletManager* bullets;
    EnemiesManager* enemies;
    EnemiesMovement* enemiesTwo;
    MapBoundaries* mapBounds;
};

#endif // GAMELOOP_H
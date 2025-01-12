#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <string>

class Player // Used to create a player class, can then be used for different players
{
public: // Inside this are functions that can be accessed when using #include "player.h"
    /* Constructor for player
     Parameters:
     Image location, SDL_Renderer
    */
    Player(const std::string& imgPath, SDL_Renderer* renderer);
    // This can be filled out with the chosen image  and renderer
    ~Player(); // The destructor for the player, frees up memory, is called automatically when the program is closed

    /* Handle inputs by reading keystate
     Parameters:
     SDL_GetKeyboardState(NULL)
    */
    void handleInput(const Uint8* keystate); // Handles the input of a player by getting the keystate

    /* Render player to screen function, player must already be created
     Parameters:
     SDL_Renderer
    */
    void render(SDL_Renderer* renderer); // Renders the player to the screen

    /* Sets the player position
     Parameters:
     double, double
    */
    void setPosition(double x, double y); // used to centre the player at the beginning, thought it can also be used to start the player from anywhere.

    double getPosX() const;
    double getPosY() const;

    double getAngle() const;

    bool getMovingBool() const;

private: // Inside this are variables which are hidden from scripts using #include "player.h", as they don't need to be changed
    SDL_Surface* playerImg;
    SDL_Texture* playerTex;
    SDL_Rect destRect;
    double posX;
    double posY;
    double rotate = 0;
    double angleRadians;
    double speed;

    bool isPlayerMoving;

    // Animation Variables

    int spriteW = 32; // Width of current frame
    int spriteH = 32; // Height of current frame
    int currentFrame = 0;
    int totalFrames = 4;

    unsigned int lastAniUpdate = 0;
    unsigned int aniSpeed = 100; // Milliseconds
};

#endif // !PLAYER_H
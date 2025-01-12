#include "player.h"

#include <SDL.h>
#include <SDL_image.h>
#include <cmath>
#include <string>

// The below function sets the player image and size, and also initialises some variables
Player::Player(const std::string& imgPath, SDL_Renderer* renderer)
    :posX(400), posY(300), destRect{ 0, 0, 0, 0 }, angleRadians(0), speed(0)
{
	playerImg = IMG_Load(imgPath.c_str());

	playerTex = SDL_CreateTextureFromSurface(renderer, playerImg);
}

Player::~Player() // This works as the destructor for the player to get rid of any memory it's taking up
{
	SDL_DestroyTexture(playerTex);
    SDL_FreeSurface(playerImg);
}

// This handles input, it passes through the current keystate and moves it accordingly
void Player::handleInput(const Uint8* keystate)
{
    // Get rotation angle and change from degrees to radians
    // So can be used for sin and cos
    angleRadians = rotate * (M_PI / 180.0f);

    // Movement speed
    speed = 5;

    // Store position changes
    double currX = 0;
    double currY = 0;

    // isPlayerMoving is used to trigger the astar to start moving towards the player
    // Forward
    if (keystate[SDL_SCANCODE_W])
    {
        isPlayerMoving = true;

        currX += speed * sin(angleRadians);
        currY -= speed * cos(angleRadians);

        // Update animation frame
        if (SDL_GetTicks() - lastAniUpdate > aniSpeed)
        {
            lastAniUpdate = SDL_GetTicks();
            currentFrame = (currentFrame + 1) % totalFrames;
        }
    }
    // Backward
    else if (keystate[SDL_SCANCODE_S])
    {
        isPlayerMoving = true;

        currX -= speed * sin(angleRadians);
        currY += speed * cos(angleRadians);

        // Update animation frame
        if (SDL_GetTicks() - lastAniUpdate > aniSpeed)
        {
            lastAniUpdate = SDL_GetTicks();
            currentFrame = (currentFrame + 1) % totalFrames;
        }
    }
    else
    {
        isPlayerMoving = false;
    }

    // Left rotate
    if (keystate[SDL_SCANCODE_A])
    {
        rotate -= speed;
    }
    // Right rotate
    if (keystate[SDL_SCANCODE_D])
    {
        rotate += speed;
    }

    // Wrap rotation to stay within 0-359 degrees, otherwise rotate number will get to large
    if (rotate < 0)
    {
        rotate += 360;
    }
    if (rotate >= 360)
    {
        rotate -= 360;
    }

    // Update position while using boundaries
    // "Magic Numbers" are taken from size of screen and player size
    if ((posX + currX - (32) > 0) && (posX + currX + (32 + 32) < 800))
    {
        posX += currX;
    }
    if ((posY + currY - (32) > 0) && (posY + currY + (32 + 32) < 640))
    {
        posY += currY;
    }
}

// The below function copies the player to the renderer, rendering is carried out in main.cpp
void Player::render(SDL_Renderer* renderer)
{
    // Calculate the row and column for the current frame
    int row = currentFrame / 2; // 2 frames per row
    int col = currentFrame % 2; // Column index within the row

    // Source rectangle for the current frame
    SDL_Rect src = { col * spriteW, row * spriteH, spriteW, spriteH };

    // destRect is used to set the player       Increasing the size of the player
    destRect = { (int)posX - (32 / 2), (int)posY - (32 / 2), (32 * 2), (32 * 2) };
    SDL_RenderCopyEx(renderer, playerTex, &src, &destRect, rotate, NULL, SDL_FLIP_HORIZONTAL);
}

// This is used to set the players starting position where it's told to
void Player::setPosition(double x, double y) 
{
    posX = x;
    posY = y;
}

double Player::getPosX() const
{
    return posX;
}

double Player::getPosY() const
{
    return posY;
}

double Player::getAngle() const
{
    return rotate;
}

bool Player::getMovingBool() const
{
    return isPlayerMoving;
}
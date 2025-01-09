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

	srcRect = { 0, 0, playerImg->w, playerImg->h };
}

Player::~Player() // This works as the destructor for the player to get rid of any memory it's taking up
{
	SDL_DestroyTexture(playerTex);
    SDL_FreeSurface(playerImg);
}

// The below function copies the player to the renderer, rendering is carried out in main.cpp
void Player::render(SDL_Renderer* renderer)
{
    // destRect is used to set the player                                        Increasing the size of the player
    destRect = { (int)posX - (playerImg->w / 2), (int)posY - (playerImg->h / 2), (playerImg->w * 2), (playerImg->h * 2) };
    SDL_RenderCopyEx(renderer, playerTex, &srcRect, &destRect, rotate, NULL, SDL_FLIP_HORIZONTAL);
}

// This handles input, it passes through the current keystate and moves it accordingly
void Player::handleInput(const Uint8* keystate)
{
    // Convert rotation angle from degrees to radians
    // Radians are and angle whose correspoing arc in a circle is equal to the radius
    angleRadians = rotate * (M_PI / 180.0f);

    // Determine movement speed
    speed = 5;

    // Move in the direction the player is facing, using sin and cos
    // Find out the angle which the player should be moving in
    if (keystate[SDL_SCANCODE_W]) 
    {
        // Sets the player moving bool to true for the enemies to use
        isPlayerMoving = true;

        // Numbers are based on window and pixel sizes

        // Check if the player is going outside the boundaries on the right
        if (posX + playerImg->w >= 800)
        {
            // Takes into consideration pixel size
            posX = 800 - 33;
        }
        else if(posX <= 0) // Check if the player is going outside the boundaries on the left
        {
            // Takes into consideration pixel size
            posX = 0 + 1;
        }
        else
        {
            // Moving code
            posX += speed * sin(angleRadians);
        }

        // Check if the player is going outside the boundaries on the bottom
        if (posY + playerImg->h >= 640)
        {
            // Takes into consideration pixel size
            posY = 640 - 33;
        }
        else if (posY <= 0) // Check if the player is going outside the boundaries on the top
        {
            // Takes into consideration pixel size
            posY = 0 + 1;
        }
        else
        {
            // Moving code
            posY -= speed * cos(angleRadians);
        }
    }
    else
    {
        // Sets the player moving bool to false for the enemies to use
        isPlayerMoving = false;
    }

    // Rotate left or right
    if (keystate[SDL_SCANCODE_A])
    {
        rotate -= speed;
    }
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
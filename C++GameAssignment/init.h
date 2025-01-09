#ifndef INIT_H
#define INIT_H

#include <SDL.h>

/* Simple initialize SDL function
 Returns:
 Will return 0 on completion
*/
int initializeSDL();

/* Create window function using SDL
Parameters:
SDL_Window, Name of window, Width of window, Height of window
Returns:
Will return 0 on completion
*/
int createWindow(SDL_Window*& window, const char* name, int windowWidth, int windowHeight);

/* Create renderer function using SDL
 Parameters:
 SDL_Window, Name of window, SDL_Renderer
 Returns:
 Will return 0 on completion
*/
int createRenderer(SDL_Window* window, SDL_Renderer*& renderer);

#endif
#include "mainmenu.h"
#include <string>

MainMenu::MainMenu(SDL_Renderer* mainRenderer, SDL_Window* mainWindow)
{
	renderer = mainRenderer;
	window = mainWindow;
}

MainMenu::~MainMenu()
{
    // Clean up all textures
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(logoTexture);
    SDL_DestroyTexture(startButtonTexture);
    SDL_DestroyTexture(endButtonTexture);

    // Clean BGM
    bgmPlayer->BGMCleanup();
}

void MainMenu::MenuInitialise()
{
	backgroundImg = IMG_Load("./Assets/Menu/MenuBackgrounds.png");
	backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundImg);
	SDL_FreeSurface(backgroundImg);

    logoImg = IMG_Load("./Assets/Menu/Logo.png");
    logoTexture = SDL_CreateTextureFromSurface(renderer, logoImg);
    SDL_FreeSurface(logoImg);

    startButtonImg = IMG_Load("./Assets/Menu/StartButton.png");
    startButtonTexture = SDL_CreateTextureFromSurface(renderer, startButtonImg);
    SDL_FreeSurface(startButtonImg);

    endButtonImg = IMG_Load("./Assets/Menu/ExitButton.png");
    endButtonTexture = SDL_CreateTextureFromSurface(renderer, endButtonImg);
    SDL_FreeSurface(endButtonImg);

    // Create bgm
    bgmPlayer = new BackgroundMusic(1);
    bgmPlayer->LoopBGM();

	isRunning = true;
}

void MainMenu::MenuUpdate()
{
	while (isRunning)
	{
		ProcessInput();

		MenuRender();
	}
}

void MainMenu::ProcessInput()
{
    SDL_Event evt;
    while (SDL_PollEvent(&evt))
    {
        // Close out the app by turning isRunning to false
        if (evt.type == SDL_QUIT)
        {
            isRunning = false;
            SET_GAME_STATE = 3; // THIS CHANGES "SCENE"
        }

        // Get mouse position
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        // Setup up outline to click within
        bool isStartHovering = (mouseX > startButtonRect.x && mouseX < startButtonRect.x + startButtonRect.w && mouseY > startButtonRect.y && mouseY < startButtonRect.y + startButtonRect.h);

        // Handle Start Button logic
        if (isStartHovering)
        {
            if (evt.type == SDL_MOUSEBUTTONDOWN)
            {
                isRunning = false;
                SET_GAME_STATE = 1; // Change to game start state
            }
        }

        // Setup up outline to click within
        bool isEndHovering = (mouseX > endButtonRect.x && mouseX < endButtonRect.x + endButtonRect.w && mouseY > endButtonRect.y && mouseY < endButtonRect.y + endButtonRect.h);

        // Handle Exit Button logic
        if (isEndHovering)
        {
            if (evt.type == SDL_MOUSEBUTTONDOWN)
            {
                isRunning = false;
                SET_GAME_STATE = 3; // Change to exit state
            }
        }
    }
}


void MainMenu::MenuRender()
{
	// Clear the renderer before drawing the new frame
	SDL_RenderClear(renderer);

	// Render the background texture
	SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);

    // Render logo
    SDL_RenderCopy(renderer, logoTexture, nullptr, &logoRect);

    // Render start button
    SDL_RenderCopy(renderer, startButtonTexture, nullptr, &startButtonRect);

    // Render exit button
    SDL_RenderCopy(renderer, endButtonTexture, nullptr, &endButtonRect);

	// Present the updated renderer to the screen
	SDL_RenderPresent(renderer);
}

// USED TO SEND THE CHANGE OF STATE TO GAME HANDLER
int MainMenu::GameStateUpdate()
{
	return SET_GAME_STATE;
}
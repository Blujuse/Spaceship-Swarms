#include "endmenu.h"
#include <string>

EndMenu::EndMenu(SDL_Renderer* mainRenderer, SDL_Window* mainWindow)
{
    renderer = mainRenderer;
    window = mainWindow;
}

EndMenu::~EndMenu()
{
    // Clean up all textures
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(logoTexture);
    SDL_DestroyTexture(restartButtonTexture);
    SDL_DestroyTexture(endButtonTexture);

    // Clean BGM
    bgmPlayer->BGMCleanup();

    // Clean font
    fontRenderer->fontClean();
}

void EndMenu::MenuInitialise()
{
    backgroundImg = IMG_Load("./Assets/Menu/MenuBackgrounds.png");
    backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundImg);
    SDL_FreeSurface(backgroundImg);

    logoImg = IMG_Load("./Assets/Menu/Logo.png");
    logoTexture = SDL_CreateTextureFromSurface(renderer, logoImg);
    SDL_FreeSurface(logoImg);

    restartButtonImg = IMG_Load("./Assets/Menu/RestartButton.png");
    restartButtonTexture = SDL_CreateTextureFromSurface(renderer, restartButtonImg);
    SDL_FreeSurface(restartButtonImg);

    endButtonImg = IMG_Load("./Assets/Menu/ExitButton.png");
    endButtonTexture = SDL_CreateTextureFromSurface(renderer, endButtonImg);
    SDL_FreeSurface(endButtonImg);

    scoreManager = new ScoreManager();

    // Setting up font and font size
    fontRenderer = std::unique_ptr<FontRenderer>(new FontRenderer(renderer));
    fontRenderer->fontInit(64);

    // Create bgm
    bgmPlayer = new BackgroundMusic(1);
    bgmPlayer->LoopBGM();

    isRunning = true;
}

void EndMenu::MenuUpdate()
{
    while (isRunning)
    {
        ProcessInput();

        MenuRender();
    }
}

void EndMenu::ProcessInput()
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
        bool isStartHovering = (mouseX > restartButtonRect.x && mouseX < restartButtonRect.x + restartButtonRect.w && mouseY > restartButtonRect.y && mouseY < restartButtonRect.y + restartButtonRect.h);

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


void EndMenu::MenuRender()
{
    // Clear the renderer before drawing the new frame
    SDL_RenderClear(renderer);

    // Render the background texture
    SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);

    // Render logo
    SDL_RenderCopy(renderer, logoTexture, nullptr, &logoRect);

    // Render start button
    SDL_RenderCopy(renderer, restartButtonTexture, nullptr, &restartButtonRect);

    // Render exit button
    SDL_RenderCopy(renderer, endButtonTexture, nullptr, &endButtonRect);

    // Render high score to screen after dcryption
    fontRenderer->fontRender("HIGH SCORE: " + std::to_string(scoreManager->GetHighScore()), 175, 270);

    // Present the updated renderer to the screen
    SDL_RenderPresent(renderer);
}

// USED TO SEND THE CHANGE OF STATE TO GAME HANDLER
int EndMenu::GameStateUpdate()
{
    return SET_GAME_STATE;
}
#include "../h/game.hpp"

#include "../h/tetris.hpp"

#include <iostream>

Game::Game()
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    this->window = SDL_CreateWindow("TetrisL2",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
    this->screenSurface = SDL_GetWindowSurface(this->window);

    this->tetris = new Tetris(this->window, this->renderer);
    this->mult = new Multiplayer(this->window, this->tetris,
        {new Tetris(this->window, this->renderer), new Tetris(this->window, this->renderer), 
         new Tetris(this->window, this->renderer), new Tetris(this->window, this->renderer),
         new Tetris(this->window, this->renderer), new Tetris(this->window, this->renderer),
         new Tetris(this->window, this->renderer), new Tetris(this->window, this->renderer),
         new Tetris(this->window, this->renderer), new Tetris(this->window, this->renderer)});
}

void Game::Start() {
    float desiredFrameRate = 60;
    float maxMS = 1000.0f / desiredFrameRate;
    Uint64 startTime = SDL_GetTicks64();
    while (!this->quit) {

        // events handling
        while (SDL_PollEvent(&this->e) != 0)
        {

            switch (this->e.type) {
                case SDL_QUIT:
                    this->quit = true;
                    break;
                case SDL_WINDOWEVENT:
                    //this->tetris->OnWindowEvent();
                    this->mult->OnWindowEvent();
                    break;
            }
        }

        // updating game states
        //this->tetris->Update();


        this->mult->Update();

        // framerate cap handling
        float timeElapsed = SDL_GetTicks64() - startTime;
        if (timeElapsed < maxMS) {
            continue;
        }
        else
            startTime = SDL_GetTicks64();


        // drawing frames
        //this->tetris->Render();
        this->mult->Render();
        SDL_RenderPresent(this->renderer);

        // logging
        std::cout << "Time elapsed: " << timeElapsed << " | FPS: " << 1000.0f / timeElapsed << '\n';
    }
}

void Game::drawQuad(const SDL_Rect& fillRect) {
    SDL_SetRenderDrawColor(this->renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(this->renderer, &fillRect);
    //Update screen
    SDL_RenderPresent(this->renderer);
}

void Game::loadTextureToScreen(std::string path) {
    //The final texture
    SDL_Texture* newTexture = NULL;
    
    //Load image at specified path
    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());

    //Create texture from surface pixels
    newTexture = SDL_CreateTextureFromSurface(this->renderer, loadedSurface);

    //Get rid of old loaded surface
    SDL_FreeSurface(loadedSurface);

    //Apply the image stretched
    SDL_Rect stretchRect;
    stretchRect.x = 100;
    stretchRect.y = 100;
    stretchRect.w = this->SCREEN_WIDTH;
    stretchRect.h = this->SCREEN_HEIGHT;

    //Clear screen
    SDL_RenderClear(this->renderer);

    //Render texture to screen
    SDL_RenderCopy(this->renderer, newTexture, NULL, &stretchRect);

    //Update screen
    SDL_RenderPresent(this->renderer);

    //Free loaded image
    SDL_DestroyTexture(newTexture);
}

Game::~Game() {
    delete this->tetris;

    //Destroy window
    SDL_DestroyWindow(this->window);

    //Quit SDL subsystems
    SDL_Quit();
}

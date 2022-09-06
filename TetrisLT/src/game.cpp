#include "../h/game.hpp"

#include "../h/tetris.hpp"
#include "../h/UI/Resources.hpp"

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_sdl.h"
#include "../imgui/imgui_impl_sdlrenderer.h"

#include <iostream>

Game::Game()
{
    // SETUP SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        printf("Error: %s\n", SDL_GetError());
        return;
    }
    TTF_Init();


    // SECTION ------------ init the members
    this->window = SDL_CreateWindow("TetrisL2",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    this->screenSurface = SDL_GetWindowSurface(this->window);


    // SECTION ------------ Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    Resources::io = &ImGui::GetIO();
    Resources::style = &ImGui::GetStyle();

    // load fonts
    Resources::fontR32 = Resources::io->Fonts->AddFontFromFileTTF("fonts/Silkscreen-Regular.ttf", 32.0f);
    Resources::fontR64 = Resources::io->Fonts->AddFontFromFileTTF("fonts/Silkscreen-Regular.ttf", 64.0f);
    Resources::fontR128 = Resources::io->Fonts->AddFontFromFileTTF("fonts/Silkscreen-Regular.ttf", 128.0f);
    Resources::fontB32 = Resources::io->Fonts->AddFontFromFileTTF("fonts/Silkscreen-Bold.ttf", 32.0f);
    Resources::fontB64 = Resources::io->Fonts->AddFontFromFileTTF("fonts/Silkscreen-Bold.ttf", 64.0f);
    Resources::fontB128 = Resources::io->Fonts->AddFontFromFileTTF("fonts/Silkscreen-Bold.ttf", 128.0f);


    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForSDLRenderer(this->window, this->renderer);
    ImGui_ImplSDLRenderer_Init(this->renderer);



    // SECTION ------------ init the members (UIs)
    /*this->mult = new UI::Multiplayer(this->window, this->tetris,
        { new Tetris(this->window, this->renderer), new Tetris(this->window, this->renderer),
         new Tetris(this->window, this->renderer), new Tetris(this->window, this->renderer),
         new Tetris(this->window, this->renderer), new Tetris(this->window, this->renderer),
         new Tetris(this->window, this->renderer), new Tetris(this->window, this->renderer),
         new Tetris(this->window, this->renderer), new Tetris(this->window, this->renderer) });*/
    this->mainMenu = new UI::Menu(this->window);

}

void Game::Start() {
    float desiredFrameRate = 60;
    float maxMS = 1000.0f / desiredFrameRate;
    Uint64 startTime = SDL_GetTicks64();
    while (!this->quit) {

        // events handling
        while (SDL_PollEvent(&this->e) != 0)
        {
            ImGui_ImplSDL2_ProcessEvent(&this->e);

            switch (this->e.type) {
                case SDL_QUIT:
                    this->quit = true;
                    break;
                case SDL_WINDOWEVENT:
                    this->mainMenu->OnWindowEvent();
                    break;
            }
        }

        // updating game states
        mainMenu->Update();


        // SECTION -------- drawing frames
        // framerate cap handling
        float timeElapsed = SDL_GetTicks64() - startTime;
        if (timeElapsed < maxMS) {
            continue;
        }
        else
            startTime = SDL_GetTicks64();


        // Start the Dear ImGui frame
        ImGui_ImplSDLRenderer_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        // clear renderer
        SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
        SDL_RenderClear(this->renderer);

        // draw UI
        mainMenu->Render();
        

        ImGui::Render();
        ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
        SDL_RenderPresent(this->renderer);


        // logging
        //std::cout << "Time elapsed: " << timeElapsed << " | FPS: " << 1000.0f / timeElapsed << '\n';
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
    delete this->mainMenu;

    //Destroy window
    SDL_DestroyWindow(this->window);

    // Cleanup
    ImGui_ImplSDLRenderer_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

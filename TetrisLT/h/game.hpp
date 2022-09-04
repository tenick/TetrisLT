#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "tetris.hpp"
#include "UI/Multiplayer.hpp"
#include <string>

class Game {
public:
    Game();
    void Start();
    ~Game();
    
private:
    void loadTextureToScreen(std::string path);
    void drawQuad(const SDL_Rect& fillRect);

    Tetris* tetris = NULL;

    Multiplayer* mult = nullptr;

    //Screen dimension constants
    int SCREEN_WIDTH = 640;
    int SCREEN_HEIGHT = 480;
    
    //The window we'll be rendering to
    SDL_Window* window = NULL;

    //The surface contained by the window
    SDL_Surface* screenSurface = NULL;

    //The window renderer
    SDL_Renderer* renderer = NULL;

    //Main loop flag
    bool quit = false;

    //Event handler
    SDL_Event e;
};

#endif
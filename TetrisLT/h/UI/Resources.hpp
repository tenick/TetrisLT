#ifndef RESOURCES_H
#define RESOURCES_H

#include "../../imgui/imgui.h"
#include <SDL.h>
#include <SDL_mixer.h>

namespace Resources {
    extern ImGuiIO* io;
    extern ImGuiStyle* style;

    // load fonts
    extern ImFont* fontR32;
    extern ImFont* fontR64;
    extern ImFont* fontR128;
    extern ImFont* fontB32;
    extern ImFont* fontB64;
    extern ImFont* fontB128;

    // load textures
    extern SDL_Texture* tetrominoesTexture;

    // load audio assets
    extern Mix_Chunk* lockSfx;
    extern Mix_Chunk* lineClearSfx;
    extern Mix_Chunk* countdownTickSfx;
}

#endif
#include "../../h/UI/Resources.hpp"

namespace Resources {
    ImGuiIO* io = nullptr;
    ImGuiStyle* style = nullptr;

    // load fonts
    ImFont* fontR32 = nullptr;
    ImFont* fontR64 = nullptr;
    ImFont* fontR128 = nullptr;
    ImFont* fontB32 = nullptr;
    ImFont* fontB64 = nullptr;
    ImFont* fontB128 = nullptr;

    // load textures
    SDL_Texture* tetrominoesTexture = NULL;

    // load audio assets
    Mix_Chunk* lockSfx = NULL;
    Mix_Chunk* lineClearSfx = NULL;
    Mix_Chunk* countdownTickSfx = NULL;
}
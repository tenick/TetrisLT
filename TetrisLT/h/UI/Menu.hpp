#ifndef MENU_H
#define MENU_H

#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_sdl.h"
#include "../../imgui/imgui_impl_sdlrenderer.h"

#include "SinglePlayer.hpp"
#include "Multiplayer.hpp"
#include "TetrisConfig.hpp"

namespace UI {
	class Menu {
    public:
		Menu(SDL_Window*& windowCtx);
        void Update();
        void Render();
        void OnWindowEvent();
        ~Menu();
    private:
        SDL_Window*& windowCtx;
        SDL_Renderer* renderCtx;

        // UIs
        SinglePlayer* singl = nullptr;
        Multiplayer* mult = nullptr;
        TetrisConfig tetrisConfigUI;

        bool showMenu = true;
        bool LANClicked = true;
        bool WANClicked = false;
	};

}

#endif
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
        UI::SinglePlayer* singl = nullptr;
        UI::Multiplayer* mult = nullptr;

        bool showMenu = true;
        bool LANClicked = true;
        bool WANClicked = false;
        

        // other UI managed by menu
        TetrisConfig tetrisConfigUI;
	};

}

#endif
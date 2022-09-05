#include "../../h/UI/Menu.hpp"
#include "../../h/UI/Resources.hpp"

namespace UI {

    Menu::Menu(SDL_Window*& windowCtx)
        : windowCtx(windowCtx), renderCtx(SDL_GetRenderer(windowCtx)), tetrisConfigUI(TetrisConfig(showTetrisConfig)) {
        // set default font
        Resources::io->FontDefault = Resources::fontR64;

        this->singl = new UI::SinglePlayer(this->windowCtx);
    }

    void Menu::OnWindowEvent() {
        this->singl->OnWindowEvent();
    }

    void Menu::Update() {
        if (this->singl->IsShowing())
            this->singl->Update();
    }

    void Menu::Render() {
        // all other UIs, priority to show, if no UIs or open, show menu
        if (this->singl->IsShowing()) {
            this->singl->Render();
            return;
        }

        if (this->showTetrisConfig) {
            this->tetrisConfigUI.Show();
            return;
        }

        // menu
        if (this->showMenu) {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->Pos);
            ImGui::SetNextWindowSize(viewport->Size);
            ImGui::SetNextWindowBgAlpha(1); // 0 -> 1 (0 transparent, 1 opaque)


            Resources::io->FontDefault = Resources::fontR64;
            Resources::style->WindowPadding = ImVec2{ 10, 10 };
            //style->Colors[ImGuiCol_WindowBg] = { 0, 0, 0, 0 };
            //style->Colors[ImGuiCol_Button] = { 0, 0, 0, 0 };
            Resources::style->FramePadding = ImVec2{ 0, 0 };

            ImGui::Begin("asda", &this->showMenu, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoResize |
                ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus);


            // logo, centered text
            ImGui::PushFont(Resources::fontB128);


            float font_size = ImGui::CalcTextSize("TetrisLT").x;

            ImGui::SetCursorPosX(ImGui::GetWindowSize().x / 2 - font_size / 2);

            ImGui::Text("TetrisLT");
            ImGui::PopFont();


            // menu stuffs
            ImGui::Text("singleplayer");
            ImGui::Button("Sprint", { ImGui::GetWindowSize().x - Resources::style->WindowPadding.x * 2, ImGui::GetFontSize() });
            if (ImGui::IsItemClicked()) {
                this->singl->Reset();
                this->singl->Show();
            }

            ImGui::Text("multiplayer");
            ImGui::RadioButton("LAN", this->LANClicked);
            bool LANClicked2 = ImGui::IsItemClicked();
            ImGui::SameLine();
            ImGui::RadioButton("WAN", this->WANClicked);
            bool WANClicked2 = ImGui::IsItemClicked();

            if (this->LANClicked && WANClicked2) {
                this->WANClicked = true;
                this->LANClicked = false;
            }
            else if (LANClicked2 && this->WANClicked) {
                this->LANClicked = true;
                this->WANClicked = false;
            }

            ImGui::Button("Create", { ImGui::GetWindowSize().x - Resources::style->WindowPadding.x * 2, ImGui::GetFontSize() });
            ImGui::Button("Join", { ImGui::GetWindowSize().x - Resources::style->WindowPadding.x * 2, ImGui::GetFontSize() });


            ImGui::Text("configurations");
            ImGui::Button("Tetris", { ImGui::GetWindowSize().x - Resources::style->WindowPadding.x * 2, ImGui::GetFontSize() });
            if (ImGui::IsItemClicked()) this->showTetrisConfig = true;

            ImGui::Button("Game", { ImGui::GetWindowSize().x - Resources::style->WindowPadding.x * 2, ImGui::GetFontSize() });


            ImGui::End();
        }
    }

    Menu::~Menu() {
        delete this->singl;
        delete this->mult;
    }
}
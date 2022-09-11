#include "../../h/UI/GameConfig.hpp"

#include "../../h/Configuration.hpp"
#include "../../h/UI/Resources.hpp"
#include "../../h/SDLEventHandler.hpp"
#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_sdl.h"
#include "../../imgui/imgui_impl_sdlrenderer.h"

#include <iostream>

namespace UI {
    void GameConfig::Show() {
        this->isShowing = true;
        this->replacementSetting = *Configuration::LastGameStates;
    }

    void GameConfig::Hide() {
        this->isShowing = false;
    }
    bool GameConfig::IsShowing() {
        return this->isShowing;
    }

    void GameConfig::Render() {
        if (this->isSettingKey) ImGui::OpenPopup("KeySetting");
        if (ImGui::BeginPopupModal("KeySetting", &this->isSettingKey, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration)) {
            ImGui::Text("Press Any Key");
            if (SDLEventHandler::CurrentKeyDown != SDL_SCANCODE_UNKNOWN) {
                bool isKeyUsed = this->replacementSetting.IsKeyUsed(SDLEventHandler::CurrentKeyDown);
                if (!isKeyUsed) {
                    *this->keyToSet = SDLEventHandler::CurrentKeyDown;
                    this->keyToSet = nullptr;
                }
                else { // show error
                    this->hasError = true;
                    this->errorMsg = std::string("Key '") + SDL_GetScancodeName(SDLEventHandler::CurrentKeyDown) + "' is already used!";
                }

                this->isSettingKey = false;
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }

        // error modal (maybe do custom MessageBox UI)
        if (this->hasError && this->errorMsg != "") ImGui::OpenPopup("Message");
        if (ImGui::BeginPopupModal("Message", &this->hasError, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove))
        {

            ImGui::Text(this->errorMsg.c_str());
            if (ImGui::Button("Close")) {
                ImGui::CloseCurrentPopup();
                this->hasError = false;
            }
            ImGui::EndPopup();
        }


        // ----------- actual gameconfig UI below -------------
        bool alwaysShow = true;
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowBgAlpha(1);



        Resources::io->FontDefault = Resources::fontR32;
        Resources::style->WindowPadding = ImVec2{ 10, 10 };
        //style->Colors[ImGuiCol_WindowBg] = { 0, 0, 0, 0 };
        //style->Colors[ImGuiCol_Button] = { 0, 0, 0, 0 };
        Resources::style->FramePadding = ImVec2{ 0, 0 };

        ImGui::Begin("asda", &alwaysShow, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus);

        ImGui::PushFont(Resources::fontB64);
        ImGui::Text("Configure - Game");
        ImGui::PopFont();


        ImGui::NewLine();
        ImGui::PushFont(Resources::fontB32);
        ImGui::Text("General");
        ImGui::PopFont();
        if (ImGui::BeginTable("table0", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
        {
            ImGui::TableNextColumn(); ImGui::Text("SFX Volume");
            ImGui::TableNextColumn(); ImGui::DragInt("##sfx", &this->replacementSetting.SFXVolume, 1.0f, 0, 100, "%d", ImGuiSliderFlags_NoInput);
            
            ImGui::EndTable();
        }


        ImGui::NewLine();
        ImGui::PushFont(Resources::fontB32);
        ImGui::Text("Singleplayer Hotkeys");
        ImGui::PopFont();
        if (ImGui::BeginTable("table1", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
        {
            ImGui::TableNextColumn(); ImGui::Text("Reset Key");
            ImGui::TableNextColumn(); ImGui::Text(SDL_GetScancodeName(this->replacementSetting.ResetKey));
            ImGui::TableNextColumn(); ImGui::Button("Set Key"); if (ImGui::IsItemClicked()) { this->isSettingKey = true; this->keyToSet = &this->replacementSetting.ResetKey; }

            ImGui::TableNextColumn(); ImGui::Text("Quit Key");
            ImGui::TableNextColumn(); ImGui::Text(SDL_GetScancodeName(this->replacementSetting.QuitKey));
            ImGui::TableNextColumn(); ImGui::Button("Set Key"); if (ImGui::IsItemClicked()) { this->isSettingKey = true; this->keyToSet = &this->replacementSetting.QuitKey; }

            ImGui::EndTable();
        }


        ImGui::NewLine();
        ImGui::PushFont(Resources::fontB32);
        ImGui::Text("Sprint");
        ImGui::PopFont();
        if (ImGui::BeginTable("table2", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
        {
            ImGui::TableNextColumn(); ImGui::Text("Start Ticks");
            ImGui::TableNextColumn(); ImGui::DragInt("##startCdTicks", &this->replacementSetting.StartCountdownTicks, 1.0f, 0, 100, "%d", ImGuiSliderFlags_NoInput);

            ImGui::TableNextColumn(); ImGui::Text("Start Tick Duration (MS)");
            ImGui::TableNextColumn(); ImGui::DragInt("##startCdTickMS", &this->replacementSetting.StartCountdownTickDurationMS, 1.0f, 0, 1000, "%d", ImGuiSliderFlags_NoInput);

            ImGui::TableNextColumn(); ImGui::Text("Reset Ticks");
            ImGui::TableNextColumn(); ImGui::DragInt("##resetCdTicks", &this->replacementSetting.ResetCountdownTicks, 1.0f, 0, 1000, "%d", ImGuiSliderFlags_NoInput);

            ImGui::TableNextColumn(); ImGui::Text("Reset Tick Duration (MS)");
            ImGui::TableNextColumn(); ImGui::DragInt("##resetCdTickMS", &this->replacementSetting.ResetCountdownTickDurationMS, 1.0f, 0, 1000, "%d", ImGuiSliderFlags_NoInput);

            ImGui::TableNextColumn(); ImGui::Text("Game Finish Delay (MS)");
            ImGui::TableNextColumn(); ImGui::DragInt("##finishDelay", &this->replacementSetting.GameFinishDelayMS, 1.0f, 0, 5000, "%d", ImGuiSliderFlags_NoInput);

            ImGui::EndTable();
        }


        ImGui::Button("Reset to Defaults");
        if (ImGui::IsItemClicked()) this->replacementSetting = GameStatesFileHandler();



        ImGui::Button("back");
        if (ImGui::IsItemClicked())
            this->Hide();
        ImGui::SameLine();
        ImGui::Button("save");
        if (ImGui::IsItemClicked())
            this->Save();

        ImGui::End();
    }

    void GameConfig::Save() {
        this->replacementSetting.WriteToFile();
        *Configuration::LastGameStates = this->replacementSetting;

        // apply to configuration
        Mix_MasterVolume((int)((float)MIX_MAX_VOLUME * ((float)Configuration::LastGameStates->SFXVolume / 100.0f)));

        // show message
        this->hasError = true;
        this->errorMsg = "Successfully saved settings!";
    }
}
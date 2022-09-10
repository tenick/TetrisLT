#include "../../h/UI/TetrisConfig.hpp"
#include "../../h/UI/Resources.hpp"
#include "../../h/Configuration.hpp"
#include "../../h/SDLEventHandler.hpp"
#include <iostream>
#include <filesystem>

namespace UI {
    void TetrisConfig::Show() {
        this->isShowing = true;

        this->previewComboBox = Configuration::LastGameStates->SelectedTetrisSettingName;
        // find last selected tetris setting
        int i = 0;
        for (auto& tetrisSetting : *Configuration::LoadedTetrisSettings) {
            if (tetrisSetting.SettingName == this->previewComboBox) {
                this->comboBoxIndexSelected = i;
                this->replacementSetting = tetrisSetting;
                strcpy_s(this->renameSettingNameBuffer, tetrisSetting.SettingName.c_str());
                strcpy_s(this->playerNameBuffer, tetrisSetting.PlayerName.c_str());
                break;
            }
            i++;
        }
    }

    void TetrisConfig::Hide() {
        this->isShowing = false;
    }
    bool TetrisConfig::IsShowing() {
        return this->isShowing;
    }

    void TetrisConfig::Render() {
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



        // tetris config
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
        ImGui::Text("Configure - Tetris");
        ImGui::PopFont();

        ImGui::InputText("##newSettingsNameInput", this->newSettingsBuffer, 100);
        ImGui::SameLine();
        ImGui::Button("New");
        if (ImGui::IsItemClicked())
            this->New();

        //const char* items[] = { "Default" };
        //static int item_current_idx = 0; // Here we store our selection data as an index.
        //const char* combo_preview_value = items[item_current_idx];  // Pass in the preview value visible before opening the combo (it could be anything)
        
        
        if (ImGui::BeginCombo("##combo1", this->previewComboBox.c_str(), 0))
        {
            for (int n = 0; n < Configuration::LoadedTetrisSettings->size(); n++)
            {
                TetrisSettingsFileHandler& tetrisSetting = Configuration::LoadedTetrisSettings->at(n);

                const bool is_selected = (this->comboBoxIndexSelected == n);
                if (ImGui::Selectable(tetrisSetting.SettingName.c_str(), is_selected)) {
                    this->comboBoxIndexSelected = n;
                    this->previewComboBox = tetrisSetting.SettingName;
                    this->replacementSetting = tetrisSetting;
                    strcpy_s(this->renameSettingNameBuffer, tetrisSetting.SettingName.c_str());
                    strcpy_s(this->playerNameBuffer, tetrisSetting.PlayerName.c_str());
                }

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }
        ImGui::SameLine();
        ImGui::Button("Delete");
        if (ImGui::IsItemClicked()) 
            this->Delete();


        if (ImGui::InputText("##settingsNameInput", this->renameSettingNameBuffer, 100, ImGuiInputTextFlags_EnterReturnsTrue, 0));
        ImGui::SameLine();
        ImGui::Button("Rename");
        if (ImGui::IsItemClicked())
            this->Rename();


        ImGui::Button("Reset to Defaults");
        if (ImGui::IsItemClicked()) this->replacementSetting = TetrisSettingsFileHandler();


        if (ImGui::BeginTable("table1", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
        {

            ImGui::TableNextColumn(); ImGui::Text("Name");
            ImGui::TableNextColumn(); if (ImGui::InputText("##1", this->playerNameBuffer, 100)) this->replacementSetting.PlayerName = this->playerNameBuffer;
            ImGui::TableNextColumn(); ImGui::Text("DAS (ms)");
            ImGui::TableNextColumn(); ImGui::InputInt("##2", &this->replacementSetting.DAS, 1, 100);
            ImGui::TableNextColumn(); ImGui::Text("ARR (ms)");
            ImGui::TableNextColumn(); ImGui::InputInt("##3", &this->replacementSetting.ARR, 1, 100);
            ImGui::TableNextColumn(); ImGui::Text("SDS (ms)");
            ImGui::TableNextColumn(); ImGui::InputInt("##4", &this->replacementSetting.SDS, 1, 100);
            ImGui::TableNextColumn(); ImGui::Text("Gravity (ms)");
            ImGui::TableNextColumn(); ImGui::InputInt("##5", &this->replacementSetting.Gravity, 1, 100);
            ImGui::TableNextColumn(); ImGui::Text("LockDelay (ms)");
            ImGui::TableNextColumn(); ImGui::InputInt("##6", &this->replacementSetting.LockDelay, 1, 100);
            ImGui::TableNextColumn(); ImGui::Text("LockDelayResetLimit");
            ImGui::TableNextColumn(); ImGui::InputInt("##7", &this->replacementSetting.LockDelayResetLimit, 1, 100);
            ImGui::TableNextColumn(); ImGui::Text("DelayAfterPieceLock (ms)");
            ImGui::TableNextColumn(); ImGui::InputInt("##8", &this->replacementSetting.DelayAfterPieceLock, 1, 100);
            ImGui::TableNextColumn(); ImGui::Text("Board Width");
            ImGui::TableNextColumn(); ImGui::InputInt("##9", &this->replacementSetting.BoardWidth, 1, 100);
            ImGui::TableNextColumn(); ImGui::Text("Board Height");
            ImGui::TableNextColumn(); ImGui::InputInt("##10", &this->replacementSetting.BoardHeight, 1, 100);
            ImGui::TableNextColumn(); ImGui::Text("Vanishing Zone Height");
            ImGui::TableNextColumn(); ImGui::InputInt("##11", &this->replacementSetting.VanishingZoneHeight, 1, 100);
            ImGui::TableNextColumn(); ImGui::Text("Enable Ghost Piece");
            ImGui::TableNextColumn(); ImGui::Checkbox("##12", &this->replacementSetting.EnableGhostPiece);

            ImGui::EndTable();
        }

        if (ImGui::BeginTable("table2", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
        {
            
            ImGui::TableNextColumn(); ImGui::Text("Move Left");
            ImGui::TableNextColumn(); ImGui::Text(SDL_GetScancodeName(this->replacementSetting.MoveLeft));
            ImGui::TableNextColumn(); ImGui::Button("Set Key"); if (ImGui::IsItemClicked()) { this->isSettingKey = true; this->keyToSet = &this->replacementSetting.MoveLeft; }

            ImGui::TableNextColumn(); ImGui::Text("Move Right");
            ImGui::TableNextColumn(); ImGui::Text(SDL_GetScancodeName(this->replacementSetting.MoveRight));
            ImGui::TableNextColumn(); ImGui::Button("Set Key"); if(ImGui::IsItemClicked()) { this->isSettingKey = true; this->keyToSet = &this->replacementSetting.MoveRight; }

            ImGui::TableNextColumn(); ImGui::Text("SoftDrop");
            ImGui::TableNextColumn(); ImGui::Text(SDL_GetScancodeName(this->replacementSetting.SoftDrop));
            ImGui::TableNextColumn(); ImGui::Button("Set Key"); if (ImGui::IsItemClicked()) { this->isSettingKey = true; this->keyToSet = &this->replacementSetting.SoftDrop; }

            ImGui::TableNextColumn(); ImGui::Text("HardDrop");
            ImGui::TableNextColumn(); ImGui::Text(SDL_GetScancodeName(this->replacementSetting.HardDrop));
            ImGui::TableNextColumn(); ImGui::Button("Set Key"); if (ImGui::IsItemClicked()) { this->isSettingKey = true; this->keyToSet = &this->replacementSetting.HardDrop; }

            ImGui::TableNextColumn(); ImGui::Text("Hold Key");
            ImGui::TableNextColumn(); ImGui::Text(SDL_GetScancodeName(this->replacementSetting.HoldTetrominoKey));
            ImGui::TableNextColumn(); ImGui::Button("Set Key"); if (ImGui::IsItemClicked()) { this->isSettingKey = true; this->keyToSet = &this->replacementSetting.HoldTetrominoKey; }

            ImGui::TableNextColumn(); ImGui::Text("Rotate CW");
            ImGui::TableNextColumn(); ImGui::Text(SDL_GetScancodeName(this->replacementSetting.RotateCW));
            ImGui::TableNextColumn(); ImGui::Button("Set Key"); if (ImGui::IsItemClicked()) { this->isSettingKey = true; this->keyToSet = &this->replacementSetting.RotateCW; }

            ImGui::TableNextColumn(); ImGui::Text("Rotate CCW");
            ImGui::TableNextColumn(); ImGui::Text(SDL_GetScancodeName(this->replacementSetting.RotateCCW));
            ImGui::TableNextColumn(); ImGui::Button("Set Key"); if (ImGui::IsItemClicked()) { this->isSettingKey = true; this->keyToSet = &this->replacementSetting.RotateCCW; }

            ImGui::TableNextColumn(); ImGui::Text("Rotate 180");
            ImGui::TableNextColumn(); ImGui::Text(SDL_GetScancodeName(this->replacementSetting.Rotate180));
            ImGui::TableNextColumn(); ImGui::Button("Set Key"); if (ImGui::IsItemClicked()) { this->isSettingKey = true; this->keyToSet = &this->replacementSetting.Rotate180; }

            ImGui::EndTable();
        }


        ImGui::Button("back");
        if (ImGui::IsItemClicked()) 
            this->Hide();
        ImGui::SameLine();
        ImGui::Button("save");
        if (ImGui::IsItemClicked())
            this->Save();

        ImGui::End();
    }


    void TetrisConfig::New() {
        std::string newSettingName = this->newSettingsBuffer;
        if (newSettingName == "") {
            this->hasError = true;
            this->errorMsg = "Can't have blank setting name";
            return;
        }


        bool existing = false;
        for (auto& tetrisSetting : *Configuration::LoadedTetrisSettings) {
            if (tetrisSetting.SettingName == newSettingName) {
                existing = true;
                break;
            }
        }

        if (existing) {
            this->hasError = true;
            this->errorMsg = std::string("'") + newSettingName + "' already exists!";
            return;
        }

        // reaching here means we can add the new settings
        TetrisSettingsFileHandler newSetting;
        newSetting.SettingName = this->newSettingsBuffer;
        newSetting.WriteToFile();
        Configuration::LoadedTetrisSettings->push_back(newSetting);

        // update game states and config window
        this->replacementSetting = newSetting;
        this->comboBoxIndexSelected = Configuration::LoadedTetrisSettings->size() - 1;
        this->previewComboBox = newSetting.SettingName;
        strcpy_s(this->renameSettingNameBuffer, newSetting.SettingName.c_str());
        strcpy_s(this->playerNameBuffer, newSetting.PlayerName.c_str());
        
        Configuration::LastGameStates->SelectedTetrisSettingName = newSetting.SettingName;
    }

    void TetrisConfig::Delete() {
        std::string filePath = std::string("config/" + this->previewComboBox + ".ini");
        std::filesystem::remove(filePath);
        Configuration::LoadedTetrisSettings->erase(Configuration::LoadedTetrisSettings->begin() + this->comboBoxIndexSelected);

        // if no more loaded settings, create default one
        if (Configuration::LoadedTetrisSettings->size() == 0) {
            TetrisSettingsFileHandler newSetting;
            newSetting.WriteToFile();
            Configuration::LoadedTetrisSettings->push_back(newSetting);
        }

        // update game states and config window
        this->replacementSetting = Configuration::LoadedTetrisSettings->at(Configuration::LoadedTetrisSettings->size() - 1);
        this->comboBoxIndexSelected = Configuration::LoadedTetrisSettings->size() - 1;
        this->previewComboBox = this->replacementSetting.SettingName;
        strcpy_s(this->renameSettingNameBuffer, this->replacementSetting.SettingName.c_str());
        strcpy_s(this->playerNameBuffer, this->replacementSetting.PlayerName.c_str());

        Configuration::LastGameStates->SelectedTetrisSettingName = this->replacementSetting.SettingName;
    }

    void TetrisConfig::Rename() {
        std::string renameSettingName = this->renameSettingNameBuffer;

        // check if no change, ignore
        if (renameSettingName == this->previewComboBox)
            return;

        // check if it's blank, show error
        if (renameSettingName == "") {
            this->hasError = true;
            this->errorMsg = "Can't have blank setting name";
            return;
        }

        // check if name is already existing, show error
        bool existing = false;
        for (auto& tetrisSetting : *Configuration::LoadedTetrisSettings) {
            if (tetrisSetting.SettingName == renameSettingName) {
                existing = true;
                break;
            }
        }
        if (existing) {
            this->hasError = true;
            this->errorMsg = "'" + renameSettingName + "' already exists!";
            return;
        }

        // reaching here means we can rename and delete the old setting 
        TetrisSettingsFileHandler& tetrisSettingToRename = Configuration::LoadedTetrisSettings->at(this->comboBoxIndexSelected);
        tetrisSettingToRename.SettingName = renameSettingName;
        tetrisSettingToRename.WriteToFile();

        // deleting
        std::string oldSettingFilePath = std::string("config/" + this->previewComboBox + ".ini");
        std::filesystem::remove(oldSettingFilePath);


        // update game states and config window
        this->replacementSetting.SettingName = renameSettingName;
        this->previewComboBox = this->replacementSetting.SettingName;
        strcpy_s(this->renameSettingNameBuffer, this->replacementSetting.SettingName.c_str());
        strcpy_s(this->playerNameBuffer, this->replacementSetting.PlayerName.c_str());

        Configuration::LastGameStates->SelectedTetrisSettingName = this->replacementSetting.SettingName;
    }

    void TetrisConfig::Save() {
        // deleting old setting file
        std::string settingFilePath = std::string("config/" + this->replacementSetting.SettingName + ".ini");
        std::filesystem::remove(settingFilePath);
        

        this->replacementSetting.WriteToFile();

        TetrisSettingsFileHandler& tetrisSettingOrig = Configuration::LoadedTetrisSettings->at(this->comboBoxIndexSelected);
        tetrisSettingOrig = this->replacementSetting;

        Configuration::LastGameStates->SelectedTetrisSettingName = this->replacementSetting.SettingName;

        // show message
        this->hasError = true;
        this->errorMsg = "Successfully saved settings!";
    }
    
}
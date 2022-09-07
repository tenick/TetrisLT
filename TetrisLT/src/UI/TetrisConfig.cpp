#include "../../h/UI/TetrisConfig.hpp"
#include "../../h/UI/Resources.hpp"
#include <iostream>

namespace UI {
    void TetrisConfig::Show() {
        this->isShowing = true;
    }

    void TetrisConfig::Hide() {
        this->isShowing = false;
    }
    bool TetrisConfig::IsShowing() {
        return this->isShowing;
    }

    void TetrisConfig::Render() {
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

        ImGui::InputText("##profileInput", profileName, strlen(profileName));
        ImGui::SameLine();
        ImGui::Button("New");

        const char* items[] = { "Default" };
        static int item_current_idx = 0; // Here we store our selection data as an index.
        const char* combo_preview_value = items[item_current_idx];  // Pass in the preview value visible before opening the combo (it could be anything)
        if (ImGui::BeginCombo("##combo1", combo_preview_value, 0))
        {
            for (int n = 0; n < IM_ARRAYSIZE(items); n++)
            {
                const bool is_selected = (item_current_idx == n);
                if (ImGui::Selectable(items[n], is_selected))
                    item_current_idx = n;

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }
        ImGui::SameLine();
        ImGui::Button("Delete");


        ImGui::Button("Reset to Defaults");


        if (ImGui::BeginTable("table1", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
        {

            ImGui::TableNextColumn(); ImGui::Text("Name");
            ImGui::TableNextColumn();
            if (ImGui::InputText("##1", name, 100, ImGuiInputTextFlags_EnterReturnsTrue, 0)) {
            }
            ImGui::TableNextColumn(); ImGui::Text("DAS");
            ImGui::TableNextColumn(); ImGui::InputInt("##2", &das, 1, 100);
            ImGui::TableNextColumn(); ImGui::Text("ARR");
            ImGui::TableNextColumn(); ImGui::InputInt("##3", &arr, 1, 100);
            ImGui::TableNextColumn(); ImGui::Text("SDS");
            ImGui::TableNextColumn(); ImGui::InputInt("##4", &sds, 1, 100);
            ImGui::TableNextColumn(); ImGui::Text("Gravity");
            ImGui::TableNextColumn(); ImGui::InputInt("##5", &gravity, 1, 100);
            ImGui::TableNextColumn(); ImGui::Text("DelayAfterLocking");
            ImGui::TableNextColumn(); ImGui::InputInt("##6", &delayAfterLocking, 1, 100);
            ImGui::TableNextColumn(); ImGui::Text("LockDelay");
            ImGui::TableNextColumn(); ImGui::InputInt("##7", &lockDelay, 1, 100);
            ImGui::TableNextColumn(); ImGui::Text("LockDelayLimit");
            ImGui::TableNextColumn(); ImGui::InputInt("##8", &lockDelayLimit, 1, 100);
            ImGui::TableNextColumn(); ImGui::Text("Enable Ghost Piece");
            ImGui::TableNextColumn(); ImGui::Checkbox("##9", &enableGhostPiece);
            ImGui::TableNextColumn(); ImGui::Text("Board Width");
            ImGui::TableNextColumn(); ImGui::InputInt("##10", &boardWidth, 1, 100);
            ImGui::TableNextColumn(); ImGui::Text("Board Height");
            ImGui::TableNextColumn(); ImGui::InputInt("##11", &boardHeight, 1, 100);
            ImGui::TableNextColumn(); ImGui::Text("Vanishing Zone Height");
            ImGui::TableNextColumn(); ImGui::InputInt("##12", &vanishingZoneHeight, 1, 100);

            ImGui::EndTable();
        }


        ImGui::Button("back");
        if (ImGui::IsItemClicked()) this->Hide();
        ImGui::SameLine();
        ImGui::Button("save");

        ImGui::End();


    }

    
}
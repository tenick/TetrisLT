#include "../../h/UI/Results.hpp"

#include "../../h/UI/Resources.hpp"
#include "../../h/helpers.hpp"

#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_sdl.h"
#include "../../imgui/imgui_impl_sdlrenderer.h"

#include <string>

namespace UI {
	void Results::Show() {
		this->isShowing = true;
	}
	void Results::Hide() {
		this->isShowing = false;
	}
	bool Results::IsShowing() {
		return this->isShowing;
	}
	void Results::Update() {

	}
	void Results::Render() {
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowBgAlpha(1); // 0 -> 1 (0 transparent, 1 opaque)


		ImGui::Begin("Results", &this->isShowing, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus);

		// results title
		ImGui::PushFont(Resources::fontB64);
		ImGui::Text("Results - Sprint");
		ImGui::PopFont();

		
		// render text stats here
		ImGui::PushFont(Resources::fontR32);
		if (ImGui::BeginTable("resultsTable", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
		{
			ImGui::TableNextColumn(); ImGui::Text("Game Duration:");
			ImGui::TableNextColumn(); ImGui::Text(Helpers::MStoMM_SSformat(this->currStats.gameDurationInMS).c_str());

			ImGui::TableNextColumn(); ImGui::Text("Lines Cleared:");
			ImGui::TableNextColumn(); ImGui::Text(std::to_string(this->currStats.LinesCleared).c_str());

			ImGui::TableNextColumn(); ImGui::Text("Pieces Locked:");
			ImGui::TableNextColumn(); ImGui::Text(std::to_string(this->currStats.PiecesLocked).c_str());

			ImGui::TableNextColumn(); ImGui::Text("PPS (Piece Per Second):");
			ImGui::TableNextColumn(); ImGui::Text(std::to_string(this->currStats.PPS).c_str());

			
			ImGui::EndTable();
		}
		ImGui::PopFont();

		// back to main menu button
		ImGui::Button("Back");
		if (ImGui::IsItemClicked()) {
			this->Hide();
		}

		ImGui::End();
	}
	void Results::UpdateStats(TetrisStats newStats) {
		this->currStats = newStats;
	}
}

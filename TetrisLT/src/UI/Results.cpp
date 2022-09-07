#include "../../h/UI/Results.hpp"

#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_sdl.h"
#include "../../imgui/imgui_impl_sdlrenderer.h"

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

		ImGui::Button("Back");
		if (ImGui::IsItemClicked()) {
			this->Hide();
		}

		// render text stats here
		ImGui::Text("stats1");
		ImGui::Text("stats2");
		ImGui::Text("stats3");

		ImGui::End();
	}
	void Results::UpdateStats(TetrisStats newStats) {
		this->currStats = newStats;
	}
}

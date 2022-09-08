#include "../../h/UI/GameOver.hpp"

#include "../../h/UI/Resources.hpp"

#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_sdl.h"
#include "../../imgui/imgui_impl_sdlrenderer.h"

#include <string>

namespace UI {
	void GameOver::Show() { this->isShowing = true; }
	bool GameOver::IsShowing() { return this->isShowing; }
	void GameOver::Hide() { this->isShowing = false; }
	void GameOver::Render() {
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowBgAlpha(1); // 0 -> 1 (0 transparent, 1 opaque)


		ImGui::Begin("Results", &this->isShowing, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus);

		// results title
		ImGui::PushFont(Resources::fontB64);
		ImGui::Text("GameOver");
		ImGui::PopFont();

		// back to main menu button
		ImGui::Button("Back");
		if (ImGui::IsItemClicked()) {
			this->Hide();
		}

		ImGui::End();
	}
}
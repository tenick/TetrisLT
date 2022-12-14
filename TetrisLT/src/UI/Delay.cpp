#include "../../h/UI/Delay.hpp"

#include "../../h/UI/Resources.hpp"
#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_sdl.h"
#include "../../imgui/imgui_impl_sdlrenderer.h"

#include <SDL.h>
#include <SDL_mixer.h>

#include <iostream>
#include <string>

namespace UI {
	Delay::Delay(int ticks, int tickDurationInMS, bool showCountdown)
		: ticks(ticks), tickDurationInMS(tickDurationInMS), showCountdown(showCountdown)
	{}

	void Delay::Show() {
		this->isShowing = true;
		this->timer.Restart();
		this->startTime = timer.CurrentTick();
	}
	void Delay::Show(int ticks, int tickDurationInMS, bool showCountdown) {
		this->ticks = ticks;
		this->tickDurationInMS = tickDurationInMS;
		this->showCountdown = showCountdown;
		this->Show();
	}

	void Delay::Update() {
		if (timer.CurrentTick() - this->startTime > this->ticks * this->tickDurationInMS)
			this->Hide();
	}

	void Delay::Render() {
		if (this->showCountdown) {
			// get current tick
			int currTick = this->timer.CurrentTick();

			int ticksPassed = currTick / this->tickDurationInMS;
			int currCountdown = this->ticks - ticksPassed;

			if (currCountdown == 0) { // done counting down
				this->Hide();
				return;
			}

			// play countdown tick sfx
			if (this->currCountdownState != currCountdown) {
				Mix_PlayChannel(0, Resources::countdownTickSfx, 0);
				this->currCountdownState = currCountdown;
			}

			std::string strCurrCountdown = std::to_string(currCountdown);

			// render countdown
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowBgAlpha(.5f); // 0 -> 1 (0 transparent, 1 opaque)


			ImGui::Begin("countdown", &this->isShowing, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoResize |
				ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus);

			auto windowSize = ImGui::GetWindowSize();
			auto textSize = ImGui::CalcTextSize(strCurrCountdown.c_str());

			ImGui::SetCursorPosX((windowSize.x - textSize.x) * 0.5f);
			ImGui::SetCursorPosY((windowSize.y - textSize.y) * 0.5f);
			ImGui::Text(strCurrCountdown.c_str());

			ImGui::End();
		}
	}

	void Delay::Hide() {
		this->isShowing = false;
	}
	bool Delay::IsShowing() {
		return this->isShowing;
	}
}
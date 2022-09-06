#include "../../h/UI/SinglePlayer.hpp"
#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_sdl.h"
#include "../../imgui/imgui_impl_sdlrenderer.h"


namespace UI {
	SinglePlayer::SinglePlayer(SDL_Window*& windowCtx)
		: windowCtx(windowCtx), renderCtx(SDL_GetRenderer(windowCtx)), tetris(new Tetris(windowCtx)), tetrisStatsHandler(this->renderCtx, timer, tetris->Viewport(), tetris->GetStats())
	{}
	
	void SinglePlayer::Update() {
		// handle keyboard
		static const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

		// check if user resets
		if (currentKeyStates[this->ResetKey]) {
			if (!this->onReset) {
				this->Reset();
				this->onReset = true;
			}
		}
		else this->onReset = false;

		// check if user exits
		if (currentKeyStates[this->BackToMenuKey]) {
			if (!this->onEsc) {
				this->Hide();
				this->onEsc = true;
			}
		}
		else this->onEsc = false;

		// check if finished
		if (this->tetris->GetStats().LinesCleared >= 40) {
			this->tetris->OnFinish();
			this->isFinished = true;
		}

		if (!this->isFinished) {
			this->tetrisStatsHandler.Update();
			this->tetris->Update();
		}
	}

	void SinglePlayer::Render() {
		this->tetris->Render();

		// add back button
		ImGui::Button("wat");

		this->tetrisStatsHandler.Render();
	}

	void SinglePlayer::OnWindowEvent() {
		int SCREEN_WIDTH;
		int SCREEN_HEIGHT;
		SDL_GetWindowSize(this->windowCtx, &SCREEN_WIDTH, &SCREEN_HEIGHT);

		SDL_Rect newViewportSize;
		newViewportSize.w = fmin(SCREEN_WIDTH, SCREEN_HEIGHT);
		newViewportSize.h = newViewportSize.w;

		newViewportSize.x = 0;
		newViewportSize.y = 0;
		if (SCREEN_HEIGHT > SCREEN_WIDTH)
			newViewportSize.y = (fmax(SCREEN_WIDTH, SCREEN_HEIGHT) - newViewportSize.h) / 2;
		else
			newViewportSize.x = (fmax(SCREEN_WIDTH, SCREEN_HEIGHT) - newViewportSize.w) / 2;

		this->tetris->SetViewport(newViewportSize);
	}


	void SinglePlayer::Show() {
		this->isShowing = true;
		this->Reset();
	}

	void SinglePlayer::Hide() {
		this->isShowing = false;
	}

	bool SinglePlayer::IsShowing() { return this->isShowing; }

	void SinglePlayer::Reset() {
		this->timer.Restart();
		this->tetris->Reset();

		// states
		this->onReset = false;
		this->onEsc = false;
	}

	SinglePlayer::~SinglePlayer() {
		delete this->tetris;
	}
}



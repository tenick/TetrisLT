#include "../../h/UI/SinglePlayer.hpp"
#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_sdl.h"
#include "../../imgui/imgui_impl_sdlrenderer.h"

#include <iostream>
#include <time.h>

namespace UI {
	SinglePlayer::SinglePlayer(SDL_Window*& windowCtx)
		: windowCtx(windowCtx), renderCtx(SDL_GetRenderer(windowCtx)), tetris(new Tetris(windowCtx)), tetrisStatsHandler(this->renderCtx, timer, tetris->Viewport(), tetris->GetStats())
	{}
	
	void SinglePlayer::Update() {
		// handle keyboard
		static const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

		// countdown
		if (this->delayCountdown.IsShowing()) {
			this->delayCountdown.Update();
			return;
		}
		else { // means countdown finished, game starting now
			if (!this->started) { // just restart timer
				timer.Restart();
				this->started = true;
			}
		}

		// update if singplayer player not finished yet
		if (!this->tetris->IsFinished()) {
			// check if user resets
			if (currentKeyStates[this->ResetKey]) {
				if (!this->onReset) {
					this->Reset();
					this->onReset = true;
					return;
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

			this->tetris->Update();
			this->tetrisStatsHandler.Update();

			// check if finished, and win game
			if (this->tetris->GetStats().LinesCleared >= this->AmountOfLinesToClearToFinish) {
				this->tetris->OnFinish();

				this->delayCountdown.Show(3, 1000, false);

				// setup results screen
				this->resultsScreen.UpdateStats(this->tetrisStatsHandler.GetLastStats());
				this->resultsScreen.Show();
			}
			else if (this->tetris->IsFinished()) { // check if topped out
				this->delayCountdown.Show(3, 1000, false);

				// show game over screen
				this->gameOverScreen.Show();
			}
		}
	}

	void SinglePlayer::Render() {
		// countdown
		if (this->delayCountdown.IsShowing())
			this->delayCountdown.Render();
		

		// tetris UI
		this->tetris->Render();
		this->tetrisStatsHandler.Render();

		if (!this->tetris->IsFinished())
			return;


		if (this->delayCountdown.IsShowing())
			return;


		// results screen
		if (this->resultsScreen.IsShowing()) {
			this->resultsScreen.Render();
			return;
		}

		// gameover screen
		if (this->gameOverScreen.IsShowing()) {
			this->gameOverScreen.Render();
			return;
		}

		// if no screens available, hide
		this->Hide();
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
		this->tetris->SetSeed(std::time(NULL));
		this->tetris->Reset();
		this->delayCountdown.Show(3, 1000, true);
	}

	void SinglePlayer::Hide() {
		this->isShowing = false;
		this->Reset();
	}

	bool SinglePlayer::IsShowing() { return this->isShowing; }

	void SinglePlayer::Reset() {
		this->delayCountdown.Show(3, 400, true);
		
		this->timer.Restart();
		this->tetris->SetSeed(std::time(NULL));
		this->tetris->Reset();
		this->tetrisStatsHandler.Reset();

		// states
		this->started = false;
		this->onReset = false;
		this->onEsc = false;

	}

	SinglePlayer::~SinglePlayer() {
		delete this->tetris;
	}
}



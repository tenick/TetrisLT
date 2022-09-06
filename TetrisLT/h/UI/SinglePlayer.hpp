#ifndef SINGLEPLAYER_H
#define SINGLEPLAYER_H

#include "../tetris.hpp"

#include "../Timer.hpp"
#include "TetrisStatsHandler.hpp"

namespace UI {
	class SinglePlayer {
	public:
		SinglePlayer(SDL_Window*& windowCtx);

		void Show();
		void Hide();
		bool IsShowing();
		void Reset();
		void OnWindowEvent(); 
		void Update();
		void Render();
		~SinglePlayer();
	private:
		SDL_Window*& windowCtx;
		SDL_Renderer* renderCtx;
		Tetris* tetris = nullptr;
		bool isShowing = false;
		Timer timer;
		UI::TetrisStatsHandler tetrisStatsHandler;

		// hotkeys
		SDL_Scancode ResetKey = SDL_SCANCODE_R;
		SDL_Scancode BackToMenuKey = SDL_SCANCODE_ESCAPE;


		// states
		bool onReset = false;
		bool onEsc = false;
		bool isFinished = false;

		// make tetris settings class (e.g. TetrisConfig tetrisConfig; )
	};

}

#endif
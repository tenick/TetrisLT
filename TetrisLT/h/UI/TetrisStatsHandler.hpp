#ifndef TETRIS_STATS_HANDLER_H
#define TETRIS_STATS_HANDLER_H

#include "../Timer.hpp"
#include "../Tetromino/TetrisStats.hpp";

#include <SDL.h>
#include <SDL_ttf.h>

#include <string>

namespace UI {
	class TetrisStatsHandler {
	public:
		TetrisStatsHandler(SDL_Renderer*& renderCtx, const Timer& timer, const SDL_Rect& tetrisViewPort, const TetrisStats& tetrisStats);
		void Render();
		void Update();
	private:
		SDL_Renderer*& renderCtx;
		const Timer& timer;
		const TetrisStats& tetrisStats;
		const SDL_Rect& tetrisViewPort;
		std::string currTime = ""; // time in MM:SS format
		std::string currPPS = "";
		TTF_Font* MainFont = NULL;
	};
}

#endif
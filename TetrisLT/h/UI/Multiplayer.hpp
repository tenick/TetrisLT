#ifndef MULTIPLAYER_H
#define MULTIPLAYER_H

#include "../tetris.hpp"
#include <vector>

namespace UI {
	class Multiplayer {
	public:
		Multiplayer(SDL_Window*& windowContext, Tetris* yourTetris, std::vector<Tetris*> enemiesTetris);
		void Update();
		void Render();
		void OnWindowEvent();
		~Multiplayer();
	private:
		SDL_Window*& windowCtx;
		Tetris* YourTetris;
		std::vector<Tetris*> EnemiesTetris;
	};
}

#endif
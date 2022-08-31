#ifndef MULTIPLAYER_H
#define MULTIPLAYER_H

#include "../tetris.hpp"
#include <vector>

class Multiplayer {
public:
	Multiplayer(SDL_Window*& windowContext, Tetris* yourTetris, std::vector<Tetris*> enemiesTetris);
	void Update();
	void Render();
	void OnWindowEvent();
private:
	SDL_Window*& windowCtx;
	Tetris* YourTetris;
	std::vector<Tetris*> EnemiesTetris;
};

#endif
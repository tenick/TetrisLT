#include "../../h/UI/Multiplayer.hpp"
#include <iostream>

Multiplayer::Multiplayer(SDL_Window*& windowContext, Tetris* yourTetris, std::vector<Tetris*> enemiesTetris)
	: windowCtx(windowContext), YourTetris(yourTetris), EnemiesTetris(enemiesTetris)
{}

void Multiplayer::OnWindowEvent() {
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	SDL_GetWindowSize(this->windowCtx, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	// sizing would be:
	// your tetris playfield 1:1
	// all enemies playfield 1:1
	// combined sizing = 2:1

	int gameSize = fmin(fmin(SCREEN_WIDTH, SCREEN_HEIGHT), fmax(SCREEN_WIDTH, SCREEN_HEIGHT) / 2);
	SDL_Rect padToCenter{};
	padToCenter.y = (SCREEN_HEIGHT - gameSize) / 2;
	padToCenter.x = (SCREEN_WIDTH - gameSize * 2) / 2;
	if (SCREEN_HEIGHT > SCREEN_WIDTH) {
		padToCenter.x = 0;
	}
	std::cout << "paddd: " << padToCenter.x << ',' << padToCenter.y << '\n';
	int r{}, c{};
	// left to right layout, wrap downwards when exceed c limit
	r = round(sqrt(this->EnemiesTetris.size()));
	c = ceil(sqrt(this->EnemiesTetris.size()));


	int tetrisViewportSize = gameSize / c;
	std::cout << r << ',' << c << ',' << tetrisViewportSize << '\n';

	if (SCREEN_HEIGHT > SCREEN_WIDTH) { // top to bottom layout, wrap rightwards when exceed r limit
		int temp = r;
		r = c;
		c = temp;
	}
	
	// draw your board
	SDL_Rect newViewportSize{ padToCenter.x, padToCenter.y, gameSize, gameSize };
	std::cout << newViewportSize.x << ',' << newViewportSize.y << ',' << newViewportSize.w << ',' << newViewportSize.h << '\n';
	this->YourTetris->SetViewport(newViewportSize);

	// draw enemies boards
	int count = 0;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (count >= this->EnemiesTetris.size())
				break;
			Tetris*& tetr = this->EnemiesTetris[count];
			SDL_Rect newViewportSize { gameSize + padToCenter.x + j * tetrisViewportSize, padToCenter.y + i * tetrisViewportSize, tetrisViewportSize, tetrisViewportSize };
			std::cout << newViewportSize.x << ',' << newViewportSize.y << ',' << newViewportSize.w << ',' << newViewportSize.h << '\n';
			tetr->SetViewport(newViewportSize);
			count++;
		}
	}
}

void Multiplayer::Update() {
	this->YourTetris->Update();
	for (Tetris*& tetr : this->EnemiesTetris) {
		tetr->Update();
	}
}
void Multiplayer::Render() {
	this->YourTetris->Render();
	for (Tetris*& tetr : this->EnemiesTetris) {
		tetr->Render();
	}
}
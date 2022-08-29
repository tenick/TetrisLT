#ifndef TETRIS_H
#define TETRIS_H

#include "Tetromino/TetrominoEnum.hpp"
#include "Tetromino/TetrominoHandler.hpp"

#include <SDL.h>

#include <vector>

class Tetris {
public:
	Tetris(SDL_Window*& windowContext, SDL_Renderer*& renderContext, int rows = 20, int columns = 10, int vanishZoneHeight=4);

	void Update();
	void Reset();
	void OnWindowEvent();
	void Render();
private:
	void UpdateViewportByWindowSize();

	// hotkeys
	SDL_Scancode ResetKey = SDL_SCANCODE_R;

	// states
	bool onReset = false;

	SDL_Window*& windowContext;
	SDL_Renderer*& renderContext;
	
	const int ROWS;
	const int COLUMNS;
	const int VANISHZONEHEIGHT;

	std::vector<std::vector<Tetromino::TetrominoEnum>> BoardState;

	Tetromino::TetrominoHandler* tetrominoHandler;

	SDL_Rect playfieldViewport;
	SDL_Rect boardViewport;
	SDL_Rect swapViewport;
	SDL_Rect next5Viewport;
};

#endif
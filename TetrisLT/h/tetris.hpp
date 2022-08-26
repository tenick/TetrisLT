#pragma once

#include <SDL.h>
#include <vector>
#include "../h/Tetromino/TetrominoBase.hpp"
#include "../h/Tetromino/TetrominoHandler.hpp"

class Tetris {
public:
	Tetris(SDL_Window*& windowContext, SDL_Renderer*& renderContext, int rows = 20, int columns = 10, int vanishZoneHeight=4);

	void Update();
	void OnWindowEvent();
	void Render();

private:
	void UpdateViewportByWindowSize();

	SDL_Window*& windowContext;
	SDL_Renderer*& renderContext;
	
	const int ROWS;
	const int COLUMNS;
	const int VANISHZONEHEIGHT;

	std::vector<std::vector<TetrominoEnum>> BoardState;

	TetrominoHandler tetrominoHandler;

	SDL_Rect boardViewport;
	SDL_Rect swapViewport;
	SDL_Rect next5Viewport;
};
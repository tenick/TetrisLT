#ifndef TETRIS_H
#define TETRIS_H

#include "Tetromino/TetrominoEnum.hpp"
#include "Tetromino/TetrominoHandler.hpp"
#include "Tetromino/TetrisStats.hpp"

#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>

class Tetris {
public:
	Tetris(SDL_Window*& windowContext, int rows = 20, int columns = 10, int vanishZoneHeight=4);

	void Update();
	void Reset();
	void OnWindowEvent();
	void OnFinish();
	bool IsFinished();
	void Render();
	void SetViewport(SDL_Rect newViewport);
	const SDL_Rect& Viewport();
	const TetrisStats& GetStats() const;
private:
	void UpdateViewportByWindowSize();

	// font
	TTF_Font* MainFont = NULL;

	// states
	bool isGhostPieceEnabled = true;
	bool isFinished = false;

	SDL_Window*& windowContext;
	SDL_Renderer* renderContext;
	
	const int ROWS;
	const int COLUMNS;
	const int VANISHZONEHEIGHT;

	std::vector<std::vector<Tetromino::TetrominoEnum>> BoardState;

	Tetromino::TetrominoHandler* tetrominoHandler;

	SDL_Rect playfieldViewport;
};

#endif
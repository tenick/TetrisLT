#pragma once

#include <SDL.h>
#include <vector>
#include "../h/Tetromino/TetrominoBase.hpp"
#include "../h/Tetromino/TetrominoHandler.hpp"

class Tetris {
public:
	Tetris(SDL_Window*& windowContext, SDL_Renderer*& renderContext, int rows = 20, int columns = 10);

	void Update();
	void OnWindowEvent();
	void Render();

private:
	void UpdateViewportByWindowSize();

	SDL_Window*& windowContext;
	SDL_Renderer*& renderContext;
	
	const int ROWS;
	const int COLUMNS;

	// settings
	int DAS = 100; // Delayed Auto Shift (ms)
	int ARR = 0;  // Auto Repeat Rate (ms)
	int SDS = 10;  // Soft Drop Speed (ms)
	int Gravity = 100; // Automatic dropping speed (ms)
	int LockDelay = 100; // Delay before locking tetromino in place (ms)
	int LockDelayResetLimit = 15; // Delay resets whenever piece is moved/rotated, after n resets it will automatically lock

	SDL_Scancode MoveLeft = SDL_SCANCODE_LEFT;
	SDL_Scancode MoveRight = SDL_SCANCODE_RIGHT;
	SDL_Scancode SoftDrop = SDL_SCANCODE_DOWN;
	SDL_Scancode HardDrop = SDL_SCANCODE_SPACE;
	SDL_Scancode RotateCW = SDL_SCANCODE_F;
	SDL_Scancode RotateCCW = SDL_SCANCODE_S;
	SDL_Scancode Rotate180 = SDL_SCANCODE_D;

	// states
	bool onHarddrop = false;
	bool onDAS = false;
	bool ARRActivated = false;
	bool SDSActivated = false;
	int currentDAS = 0;
	int currentARR = 0;
	int currentSDS = 0;

	bool onCWRotate = false;
	bool onCCWRotate = false;
	bool on180Rotate = false;

	std::vector<std::vector<TetrominoEnum>> BoardState;

	TetrominoHandler tetrominoHandler;

	SDL_Rect boardViewport;
	SDL_Rect swapViewport;
	SDL_Rect next5Viewport;
};
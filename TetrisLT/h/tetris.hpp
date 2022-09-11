#ifndef TETRIS_H
#define TETRIS_H

#include "TetrisSettingsFileHandler.hpp"
#include "../h/Configuration.hpp"
#include "Tetromino/TetrominoEnum.hpp"
#include "Tetromino/TetrominoHandler.hpp"
#include "Tetromino/TetrisStats.hpp"

#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>

class Tetris {
public:
	Tetris(SDL_Window*& windowContext);

	void Update();
	void Reset();
	void OnWindowEvent();
	void OnFinish();
	bool IsFinished();
	void Render();
	void SetViewport(SDL_Rect newViewport);
	void SetSeed(int newSeed);
	const SDL_Rect& Viewport();
	const TetrisStats& GetStats() const;
private:
	void UpdateViewportByWindowSize();

	// font
	TTF_Font* MainFont = NULL;

	// states
	bool isFinished = false;

	SDL_Window*& windowContext;
	SDL_Renderer* renderContext;
	
	// tetris settings
	TetrisSettingsFileHandler TetrisSettings = Configuration::CurrentSelectedTetrisSetting();

	int& ROWS = TetrisSettings.BoardHeight;
	int& COLUMNS = TetrisSettings.BoardWidth;
	int& VANISHZONEHEIGHT = TetrisSettings.VanishingZoneHeight;

	bool& isGhostPieceEnabled = TetrisSettings.EnableGhostPiece;
	
	// playfield
	std::vector<std::vector<Tetromino::TetrominoEnum>> BoardState;
	Tetromino::TetrominoHandler* tetrominoHandler;

	SDL_Rect playfieldViewport;
};

#endif
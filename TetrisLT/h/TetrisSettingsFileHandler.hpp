#ifndef TETRIS_SETTINGS_FILE_HANDLER_H
#define TETRIS_SETTINGS_FILE_HANDLER_H

#include <SDL.h>
#include <time.h>
#include <string>
#include <random>


struct TetrisSettingsFileHandler {
	std::string SettingName = std::string("Setting#") + std::to_string(std::mt19937(time(NULL))() % 9999);
	std::string OldSettingName = SettingName;
	
	std::string PlayerName = std::string("Guest#") + std::to_string(std::mt19937(time(NULL))() % 9999);

	int DAS = 120; // Delayed Auto Shift (ms)
	int ARR = 0;  // Auto Repeat Rate (ms)
	int SDS = 10;  // Soft Drop Speed (ms)
	int Gravity = 500; // Automatic dropping speed (ms)
	int LockDelay = 500; // Delay before locking tetromino in place (ms)
	int LockDelayResetLimit = 15; // Delay resets whenever piece is moved/rotated, after n resets it will automatically lock
	int DelayAfterPieceLock = 100; // ms delay on piece lock (to prevent accidental hard drops)

	int BoardWidth = 10;
	int BoardHeight = 20;
	int VanishingZoneHeight = 20;
	bool EnableGhostPiece = true;

	SDL_Scancode MoveLeft = SDL_SCANCODE_LEFT;
	SDL_Scancode MoveRight = SDL_SCANCODE_RIGHT;
	SDL_Scancode SoftDrop = SDL_SCANCODE_DOWN;
	SDL_Scancode HardDrop = SDL_SCANCODE_SPACE;
	SDL_Scancode HoldTetrominoKey = SDL_SCANCODE_LSHIFT;
	SDL_Scancode RotateCW = SDL_SCANCODE_F;
	SDL_Scancode RotateCCW = SDL_SCANCODE_S;
	SDL_Scancode Rotate180 = SDL_SCANCODE_D;

	bool LoadFromFile(std::string fileName);
	void WriteToFile();
	bool IsKeyUsed(SDL_Scancode key);
};

#endif
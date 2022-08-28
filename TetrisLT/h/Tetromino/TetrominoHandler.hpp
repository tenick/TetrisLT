#ifndef TETROMINO_HANDLER_H
#define TETROMINO_HANDLER_H

#include "../Randomizer/RandomizerBase.hpp"
#include "../Randomizer/BagOf7.hpp"
#include "../RotationSystem/SRS.hpp"
#include "TetrominoBase.hpp"
#include "TetrominoEnum.hpp"
#include "TetrominoMoveEnum.hpp"
#include "TetrominoRotationEnum.hpp"

#include <SDL.h>

using namespace Randomizer;
using namespace RotationSystem;

namespace Tetromino {
	class TetrominoHandler {
	public:
		TetrominoHandler() = delete;
		TetrominoHandler(std::vector<std::vector<TetrominoEnum>>& boardState,
						 RandomizerBase* randomizer = new BagOf7(),
						 RotationSystemBase* rotationSystemBase = new SRS());
		
		TetrominoBase* EnumToTetromino(TetrominoEnum tetrEnum);
		
		bool Move(TetrominoMoveEnum moveDir);
		bool Rotate(TetrominoRotationEnum rotateDir);
		void Lock();
		void Next();
		void Update();
		TetrominoEnum GetHoldTetromino();
		TetrominoBase* GetCurrentTetromino();

		RotationSystemEnum GetRotationSystemEnumEquivalent();

		const std::array<TetrominoEnum, 5> PeekNext5Tetrominos();
		~TetrominoHandler();
	private:
		// helpers
		void ResetLock();
		void ResetLockDelay(int increment=1);
		void StartLockDelay();

		// playfield
		std::vector<std::vector<TetrominoEnum>>& BoardState;
		const int BoardHeight;
		const int BoardWidth;
		
		// rotation system
		RotationSystemBase* rotationSystem;

		// randomizer
		RandomizerBase* randomizer;

		TetrominoBase* currentTetromino = nullptr;
		TetrominoEnum holdTetromino = _;

		// settings
		int DAS = 120; // Delayed Auto Shift (ms)
		int ARR = 0;  // Auto Repeat Rate (ms)
		int SDS = 10;  // Soft Drop Speed (ms)
		int Gravity = 200; // Automatic dropping speed (ms)
		int LockDelay = 400; // Delay before locking tetromino in place (ms)
		int LockDelayResetLimit = 15; // Delay resets whenever piece is moved/rotated, after n resets it will automatically lock

		SDL_Scancode MoveLeft = SDL_SCANCODE_LEFT;
		SDL_Scancode MoveRight = SDL_SCANCODE_RIGHT;
		SDL_Scancode SoftDrop = SDL_SCANCODE_DOWN;
		SDL_Scancode HardDrop = SDL_SCANCODE_SPACE;
		SDL_Scancode HoldTetrominoKey = SDL_SCANCODE_LSHIFT;
		SDL_Scancode RotateCW = SDL_SCANCODE_F;
		SDL_Scancode RotateCCW = SDL_SCANCODE_S;
		SDL_Scancode Rotate180 = SDL_SCANCODE_D;

		// states
		bool onHarddrop = false;

		bool SDSActivated = false;
		int currentSDS = 0;

		bool isLocking = false;
		int currentLockTime = 0;
		int currentLockReset = 0;

		int holdLimit = 1;
		int currentHold = 0;

		bool onLeftDAS = false;
		bool leftARRActivated = false;
		int currentLeftDAS = 0;
		int currentLeftARR = 0;

		bool onRightDAS = false;
		bool rightARRActivated = false;
		int currentRightDAS = 0;
		int currentRightARR = 0;

		
		bool onCWRotate = false;
		bool onCCWRotate = false;
		bool on180Rotate = false;
	};
}

#endif
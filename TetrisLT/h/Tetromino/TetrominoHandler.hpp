#ifndef TETROMINO_HANDLER_H
#define TETROMINO_HANDLER_H

class Tetris ;

#include "../tetris.hpp"
#include "../TetrisSettingsFileHandler.hpp"
#include "../Randomizer/RandomizerBase.hpp"
#include "../Randomizer/BagOf7.hpp"
#include "../RotationSystem/SRS.hpp"
#include "TetrominoBase.hpp"
#include "TetrominoEnum.hpp"
#include "TetrominoMoveEnum.hpp"
#include "TetrominoRotationEnum.hpp"
#include "TetrisStats.hpp"

#include <SDL.h>

#include <queue>

using namespace Randomizer;
using namespace RotationSystem;

namespace Tetromino {
	class TetrominoHandler {
	public:
		TetrominoHandler(const TetrisSettingsFileHandler& tetrisSettings,
						 std::vector<std::vector<TetrominoEnum>>& boardState,
						 std::queue<int>& garbageQueue,
						 bool& isFinished,
						 Tetris* targetOpponent = NULL,
						 RandomizerBase* randomizer = new BagOf7(),
						 RotationSystemBase* rotationSystemBase = new SRS());

		TetrominoBase* EnumToTetromino(TetrominoEnum tetrEnum);
		
		bool Move(TetrominoMoveEnum moveDir);
		bool Rotate(TetrominoRotationEnum rotateDir);
		void Lock();
		void Next();
		void Reset();
		void Update();
		void OnFinish();
		void SetSeed(int newSeed);
		const TetrisStats& CurrentStats() const;
		TetrominoEnum GetHoldTetromino();
		TetrominoBase*& GetCurrentTetromino();

		RotationSystemEnum GetRotationSystemEnumEquivalent();

		const std::array<TetrominoEnum, 5> PeekNext5Tetrominos();
		~TetrominoHandler();
	private:
		// opponent
		Tetris* targetOpponent = NULL;

		// parent tetris garbage queue
		std::queue<int>& garbageQueue;

		// tetris state
		bool& isFinished;

		// helpers
		void ResetLock();
		void ResetLockDelay();
		void StartLockDelay();

		// gameplay stats
		TetrisStats tetrisStats;

		// settings
		const TetrisSettingsFileHandler& TetrisSettings;
		
		// playfield
		std::vector<std::vector<TetrominoEnum>>& BoardState;
		int BoardHeight = BoardState.size();
		int BoardWidth = BoardState[0].size();

		// randomizer
		RandomizerBase* randomizer;
		
		// rotation system
		RotationSystemBase* rotationSystem;

		TetrominoBase* currentTetromino = nullptr;
		TetrominoEnum holdTetromino = _;


		const int& DAS = TetrisSettings.DAS; // Delayed Auto Shift (ms)
		const int& ARR = TetrisSettings.ARR;  // Auto Repeat Rate (ms)
		const int& SDS = TetrisSettings.SDS;  // Soft Drop Speed (ms)
		const int& Gravity = TetrisSettings.Gravity; // Automatic dropping speed (ms)
		const int& LockDelay = TetrisSettings.LockDelay; // Delay before locking tetromino in place (ms)
		const int& LockDelayResetLimit = TetrisSettings.LockDelayResetLimit; // Delay resets whenever piece is moved/rotated, after n resets it will automatically lock
		const int& DelayAfterPieceLock = TetrisSettings.DelayAfterPieceLock; // ms delay on piece lock (to prevent accidental hard drops)
		const bool& isGhostEnabled = TetrisSettings.EnableGhostPiece;

		const SDL_Scancode& MoveLeft = TetrisSettings.MoveLeft;
		const SDL_Scancode& MoveRight = TetrisSettings.MoveRight;
		const SDL_Scancode& SoftDrop = TetrisSettings.SoftDrop;
		const SDL_Scancode& HardDrop = TetrisSettings.HardDrop;
		const SDL_Scancode& HoldTetrominoKey = TetrisSettings.HoldTetrominoKey;
		const SDL_Scancode& RotateCW = TetrisSettings.RotateCW;
		const SDL_Scancode& RotateCCW = TetrisSettings.RotateCCW;
		const SDL_Scancode& Rotate180 = TetrisSettings.Rotate180;

		// states
		bool onHarddrop = false;

		bool isDelayingAfterPieceLock = false;
		int delayAfterPieceLockStartTime = 0;

		int gravityStartTime = 0;

		bool SDSActivated = false;
		int currentSDS = 0;

		bool isLocking = false;
		int highestRowOffsetReached = 0; // the lowest the piece is on the board, if new lowest reached, reset lock
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
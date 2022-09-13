#include "../../h/Tetromino/TetrominoHandler.hpp"

#include "../../h/Tetromino/I.hpp"
#include "../../h/Tetromino/J.hpp"
#include "../../h/Tetromino/L.hpp"
#include "../../h/Tetromino/O.hpp"
#include "../../h/Tetromino/S.hpp"
#include "../../h/Tetromino/T.hpp"
#include "../../h/Tetromino/Z.hpp"
#include "../../h/Tetromino/TetrominoHelpers.hpp"

#include "../../h/UI/Resources.hpp"

#include <SDL.h>
#include <SDL_mixer.h>

#include <iostream>
#include <time.h>
#include <random>

namespace Tetromino {
	TetrominoHandler::TetrominoHandler(const TetrisSettingsFileHandler& tetrisSettings,
									   std::vector<std::vector<TetrominoEnum>>& boardState,
									   std::queue<int>& garbageQueue,
									   bool& isFinished,
									   Tetris* targetOpponent,
									   Randomizer::RandomizerBase* randomizer,
									   RotationSystem::RotationSystemBase* rotationSystemBase)
		:	TetrisSettings(tetrisSettings),
		    BoardState(boardState),
			garbageQueue(garbageQueue),
			isFinished(isFinished),
			targetOpponent(targetOpponent),
			randomizer(randomizer),
			rotationSystem(rotationSystemBase),
			currentTetromino(EnumToTetromino(randomizer->Next()))
	{
		gravityStartTime = SDL_GetTicks64();
		this->BoardHeight = BoardState.size();
		this->BoardWidth = BoardState[0].size();

		this->tetrisStats.PlayerName = this->TetrisSettings.PlayerName;
	}

	void TetrominoHandler::SetSeed(int newSeed) {
		this->randomizer->SetSeed(newSeed);
	}


	void TetrominoHandler::Reset() {
		randomizer->Reset();

		delete this->currentTetromino;
		this->currentTetromino = EnumToTetromino(randomizer->Next());
		this->holdTetromino = _;

		// reset stats
		this->tetrisStats = TetrisStats();
		this->tetrisStats.PlayerName = this->TetrisSettings.PlayerName;

		// reset board size
		this->BoardHeight = BoardState.size();
		this->BoardWidth = BoardState[0].size();

		// reset states
		this->onHarddrop = false;

		this->isDelayingAfterPieceLock = false;
		this->delayAfterPieceLockStartTime = 0;

		this->gravityStartTime = 0;

		this->SDSActivated = false;
		this->currentSDS = 0;

		this->isLocking = false;
		this->highestRowOffsetReached = 0;
		this->currentLockTime = 0;
		this->currentLockReset = 0;

		this->holdLimit = 1;
		this->currentHold = 0;

		this->onLeftDAS = false;
		this->leftARRActivated = false;
		this->currentLeftDAS = 0;
		this->currentLeftARR = 0;

		this->onRightDAS = false;
		this->rightARRActivated = false;
		this->currentRightDAS = 0;
		this->currentRightARR = 0;


		this->onCWRotate = false;
		this->onCCWRotate = false;
		this->on180Rotate = false;
	}


	TetrominoBase* TetrominoHandler::EnumToTetromino(TetrominoEnum tetrEnum) {
		auto& rotationStates = this->rotationSystem->GetTetrominoRotationStates().at(tetrEnum);
		int pieceColumnSpawn = (this->BoardWidth - rotationStates[0][0].size()) / 2;
		switch (tetrEnum) {
		case I_:
			return new I(this->rotationSystem, 0, pieceColumnSpawn);
		case J_:
			return new J(this->rotationSystem, 0, pieceColumnSpawn);
		case L_:
			return new L(this->rotationSystem, 0, pieceColumnSpawn);
		case O_:
			return new O(this->rotationSystem, 0, pieceColumnSpawn);
		case S_:
			return new S(this->rotationSystem, 0, pieceColumnSpawn);
		case T_:
			return new T(this->rotationSystem, 0, pieceColumnSpawn);
		case Z_:
			return new Z(this->rotationSystem, 0, pieceColumnSpawn);
		}
	}

	RotationSystem::RotationSystemEnum TetrominoHandler::GetRotationSystemEnumEquivalent() {
		return this->rotationSystem->GetRotationSystemEnumEquivalent();
	}

	const TetrisStats& TetrominoHandler::CurrentStats() const {
		return this->tetrisStats;
	}

	void TetrominoHandler::Lock() {
		// guarantee hard drop
		while (this->Move(M_D))
			continue;

		auto currentTetromino = this->GetCurrentTetromino();
		auto currentTetrominoState = currentTetromino->GetCurrentRotationState();

		// add current tetromino to the board state
		for (int r = 0; r < currentTetromino->Height(); r++) {
			for (int c = 0; c < currentTetromino->Width(); c++) {
				int boardR = r + currentTetromino->RowOffset;
				int boardC = c + currentTetromino->ColumnOffset;
				if (currentTetrominoState[r][c] != _)
					this->BoardState[boardR][boardC] = currentTetrominoState[r][c];
			}
		}

		// play lock sfx
		Mix_PlayChannel(0, Resources::lockSfx, 0);

		// clear lines
		std::vector<std::vector<TetrominoEnum>> newBoard(this->BoardHeight, std::vector<TetrominoEnum>(this->BoardWidth, _));
		int rowToAdd = 0;
		for (int r = this->BoardHeight - 1; r >= 0; r--) {
			const std::vector<TetrominoEnum>& column = this->BoardState[r];
			bool columnClearable = true;
			for (int c = 0; c < this->BoardWidth; c++) {
				if (this->BoardState[r][c] == _) {
					columnClearable = false;
					break;
				}
			}
			if (!columnClearable)
				newBoard[r + rowToAdd] = column;
			else
				rowToAdd++;
		}
		this->BoardState = newBoard;



		// check if there was a line clear
		if (rowToAdd > 0) {
			// play line clear SFX
			Mix_PlayChannel(1, Resources::lineClearSfx, 0);

			// check if we have an opponent, send lines to it
			if (this->targetOpponent != NULL) {

				// calculate how many lines to send to opponent
				//...

				this->targetOpponent->ReceiveGarbage(rowToAdd);
			}
		}
		else { // if there's no line clear, garbage will be applied
			// apply the queued garbages to board (if there are any)
			if (!this->garbageQueue.empty()) {
				int garbageAmount = this->garbageQueue.front();
				this->garbageQueue.pop();

				// if garbage is higher than board height then gameover
				if (garbageAmount > this->BoardHeight) {
					this->OnFinish();
					return;
				}

				// get random open spot for the garbage line
				int seed = time(NULL);
				std::minstd_rand rand(seed);
				int openSpotIndex = rand() % this->BoardWidth;

				// create new clean board with just the garbage at the bottom
				std::vector<std::vector<TetrominoEnum>> newBoard(this->BoardHeight, std::vector<TetrominoEnum>(this->BoardWidth, _));
				for (int i = 0; i < garbageAmount; i++) {
					for (int c = 0; c < this->BoardWidth; c++) {
						if (c != openSpotIndex)
							newBoard[this->BoardHeight - i - 1][c] = G_;
					}
				}

				// find highest row with tetromino piece present
				bool found = false;
				int highestRowIndexWithPiece = 0;
				for (int r = 0; r < this->BoardHeight; r++) {
					const std::vector<TetrominoEnum>& column = this->BoardState[r];
					for (int c = 0; c < this->BoardWidth; c++) {
						if (column[c] != _) {
							found = true;
							highestRowIndexWithPiece = r;
							break;
						}
					}
					if (found)
						break;
				}

				// calculate how much of the current board we need to append to the new board
				int amountOfTheStackToAppend = this->BoardHeight - highestRowIndexWithPiece;

				// check if we can append the amount calculated, if not, gameover
				if (amountOfTheStackToAppend + garbageAmount > this->BoardHeight) {
					this->OnFinish();
					return;
				}

				// add the current stack above the garbage
				for (int r = this->BoardHeight - 1; r >= highestRowIndexWithPiece; r--) {
					for (int c = 0; c < this->BoardWidth; c++) {
						TetrominoEnum currCell = this->BoardState[r][c];

						int rowToInsert = r - garbageAmount;
						newBoard[rowToInsert][c] = currCell;
					}
				}

				this->BoardState = newBoard;
			}
		}
		


		// get next piece
		this->Next();

		// update states
		this->currentHold = 0;
		this->highestRowOffsetReached = 0;

		// update stats
		this->tetrisStats.PiecesLocked++;
		this->tetrisStats.LinesCleared += rowToAdd;

		// start delay after locking piece (preventing accidental hard drops)
		this->isDelayingAfterPieceLock = true;
		this->delayAfterPieceLockStartTime = SDL_GetTicks64();
	}

	void TetrominoHandler::OnFinish() {
		this->isFinished = true;

		// replace current pieces in board with garbage (to indicate it's finished)
		for (int r = 0; r < this->BoardState.size(); r++) {
			for (int c = 0; c < this->BoardState[r].size(); c++) {
				TetrominoEnum tetrEnum = this->BoardState[r][c];
				if (tetrEnum != _)
					this->BoardState[r][c] = G_;
			}
		}
	}

	void TetrominoHandler::ResetLock() {
		this->isLocking = false;
		this->currentLockReset = 0;
	}

	void TetrominoHandler::StartLockDelay() {
		if (!this->isLocking) {
			this->isLocking = true;
			this->currentLockTime = SDL_GetTicks64();
		}
	}

	void TetrominoHandler::ResetLockDelay() {
		if (!CanMove(this->BoardState, 
					this->currentTetromino->GetCurrentRotationState(),
					this->currentTetromino->ColumnOffset, 
					this->currentTetromino->RowOffset + 1)) // piece can't move down, meaning it's sitting on pieces/floor
			this->currentLockReset++;

		if (this->currentLockReset >= this->LockDelayResetLimit) {
			this->Lock();
			this->ResetLock();
		}
		else
			this->currentLockTime = SDL_GetTicks64();
	}

	void TetrominoHandler::Update() {
		// handle keyboard
		static const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

		// TODO: Multiplayer
		// TODO: Loss conditions
		// TODO: Scoring

		// gravity
		if (!this->SDSActivated && SDL_GetTicks64() - gravityStartTime >= this->Gravity) {
			if (!this->Move(M_D))
				this->StartLockDelay();
			else {
				if (this->currentTetromino->RowOffset <= this->highestRowOffsetReached)
					this->ResetLockDelay();
			}

			if (this->currentTetromino->RowOffset > this->highestRowOffsetReached) {
				this->ResetLock();
				this->highestRowOffsetReached = this->currentTetromino->RowOffset;
			}

			gravityStartTime = SDL_GetTicks64();
		}
	
		// harddrop input
		if (currentKeyStates[this->HardDrop])
		{
			if (this->isDelayingAfterPieceLock) {
				if (SDL_GetTicks64() - this->delayAfterPieceLockStartTime >= this->DelayAfterPieceLock) {
					this->isDelayingAfterPieceLock = false;
				}
			}
			else if (!this->onHarddrop) {
				this->Lock();
				this->ResetLock();

				this->onHarddrop = true;
			}
		}
		else
			this->onHarddrop = false;

		// softdrop input
		if (currentKeyStates[this->SoftDrop])
		{
			if (!this->SDSActivated) {
				if (!this->Move(M_D))
					this->StartLockDelay();
				else {
					if (this->currentTetromino->RowOffset <= this->highestRowOffsetReached)
						this->ResetLockDelay();
				}

				if (this->currentTetromino->RowOffset > this->highestRowOffsetReached) {
					this->ResetLock();
					this->highestRowOffsetReached = this->currentTetromino->RowOffset;
				}

				this->currentSDS = SDL_GetTicks64();
				this->SDSActivated = true;
			}
			else if (this->SDSActivated && SDL_GetTicks64() - this->currentSDS >= this->SDS) {
				if (!this->Move(M_D))
					this->StartLockDelay();
				else {
					if (this->currentTetromino->RowOffset <= this->highestRowOffsetReached)
						this->ResetLockDelay();
				}

				if (this->currentTetromino->RowOffset > this->highestRowOffsetReached) {
					this->ResetLock();
					this->highestRowOffsetReached = this->currentTetromino->RowOffset;
				}

				this->currentSDS = SDL_GetTicks64();
			}

			gravityStartTime = SDL_GetTicks64();
		}
		else {
			this->SDSActivated = false;
			this->currentSDS = 0;
		}

		// lock delay handling
		if (this->isLocking && SDL_GetTicks64() - this->currentLockTime >= this->LockDelay) {
			this->Lock();
			this->ResetLock();
		}


		// hold tetromino
		if (currentKeyStates[this->HoldTetrominoKey]) {
			if (this->holdTetromino == _) { // no hold yet
				this->holdTetromino = this->currentTetromino->GetTetrominoEnumEquivalent();
				delete this->currentTetromino;
				this->currentTetromino = EnumToTetromino(this->randomizer->Next());
				this->currentHold++;

				this->ResetLock();
			}
			else {
				if (this->currentHold < this->holdLimit) {
					TetrominoEnum temp = this->holdTetromino;
					this->holdTetromino = this->currentTetromino->GetTetrominoEnumEquivalent();
					delete this->currentTetromino;
					this->currentTetromino = EnumToTetromino(temp);
					this->currentHold++;

					this->ResetLock();
				}
			}

			
		}

		// rotation CW, CCW, and 180
		if (currentKeyStates[this->RotateCW]) {
			if (!this->onCWRotate) {
				if (this->Rotate(TetrominoRotationEnum::R_CW) && this->isLocking)
					this->ResetLockDelay();
				this->onCWRotate = true;
			}
		}
		else
			this->onCWRotate = false;
		if (currentKeyStates[this->RotateCCW]) {
			if (!this->onCCWRotate) {
				if(this->Rotate(TetrominoRotationEnum::R_CCW) && this->isLocking)
					this->ResetLockDelay();
				this->onCCWRotate = true;
			}
		}
		else
			this->onCCWRotate = false;
		if (currentKeyStates[this->Rotate180]) {
			if (!this->on180Rotate) {
				if(this->Rotate(TetrominoRotationEnum::R_180) && this->isLocking)
					this->ResetLockDelay();
				this->on180Rotate = true;
			}
		}
		else
			this->on180Rotate = false;


		// move left
		if (currentKeyStates[this->MoveLeft] && !this->rightARRActivated)
		{
			if (!this->leftARRActivated) {
				if (!this->onLeftDAS) {
					if (this->Move(M_L) && this->isLocking)
						this->ResetLockDelay();
					this->onLeftDAS = true;
					this->currentLeftDAS = SDL_GetTicks64();
				}
				else if (this->onLeftDAS && SDL_GetTicks64() - this->currentLeftDAS >= this->DAS) {
					this->leftARRActivated = true;
					this->currentLeftARR = SDL_GetTicks();
				}
			}
			else if (this->leftARRActivated && SDL_GetTicks64() - this->currentLeftARR >= this->ARR) {
				if (this->Move(M_L) && this->isLocking)
					this->ResetLockDelay();
				this->currentLeftARR = SDL_GetTicks();
			}
		}
		else {
			this->leftARRActivated = false;
			this->onLeftDAS = false;
			this->currentLeftDAS = 0;
			this->currentLeftARR = 0;
		}

		// move right
		if (currentKeyStates[this->MoveRight] && !this->leftARRActivated)
		{
			if (!this->rightARRActivated) {
				if (!this->onRightDAS) {
					if(this->Move(M_R) && this->isLocking)
						this->ResetLockDelay();
					this->onRightDAS = true;
					this->currentRightDAS = SDL_GetTicks64();
				}
				else if (this->onRightDAS && SDL_GetTicks64() - this->currentRightDAS >= this->DAS) {
					this->rightARRActivated = true;
					this->currentRightARR = SDL_GetTicks();
				}
			}
			else if (this->rightARRActivated && SDL_GetTicks64() - this->currentRightARR >= this->ARR) {
				if (this->Move(M_R) && this->isLocking)
					this->ResetLockDelay();
				this->currentRightARR = SDL_GetTicks();
			}
		}
		else {
			this->rightARRActivated = false;
			this->onRightDAS = false;
			this->currentRightDAS = 0;
			this->currentRightARR = 0;
		}
	}

	bool TetrominoHandler::Move(TetrominoMoveEnum moveDir) {
		bool canMove = false;
		switch (moveDir) {
			case M_L:
				canMove = CanMove(this->BoardState,
								  this->currentTetromino->GetCurrentRotationState(),
								  this->currentTetromino->ColumnOffset - 1, 
								  this->currentTetromino->RowOffset);
				if (canMove)
					this->currentTetromino->ColumnOffset -= 1;
				break;
			case M_R:
				canMove = CanMove(this->BoardState,
								  this->currentTetromino->GetCurrentRotationState(),
								  this->currentTetromino->ColumnOffset + 1, 
								  this->currentTetromino->RowOffset);
				if (canMove)
					this->currentTetromino->ColumnOffset += 1;
				break;
			case M_D:
				canMove = CanMove(this->BoardState,
								  this->currentTetromino->GetCurrentRotationState(),
								  this->currentTetromino->ColumnOffset, 
								  this->currentTetromino->RowOffset + 1);
				if (canMove)
					this->currentTetromino->RowOffset += 1;
				break;
		}
		return canMove;
	}

	bool TetrominoHandler::Rotate(TetrominoRotationEnum rotateDir) {
		return this->rotationSystem->Rotate(this->BoardState, this->currentTetromino, rotateDir);
	}

	void TetrominoHandler::Next() {
		delete this->currentTetromino;
		this->currentTetromino = EnumToTetromino(this->randomizer->Next());
	}

	TetrominoEnum TetrominoHandler::GetHoldTetromino() {
		return this->holdTetromino;
	}

	TetrominoBase*& TetrominoHandler::GetCurrentTetromino() {
		return this->currentTetromino;
	}

	const std::array<TetrominoEnum, 5> TetrominoHandler::PeekNext5Tetrominos() {
		return this->randomizer->PeekNext5();
	}

	TetrominoHandler::~TetrominoHandler() {
		delete this->rotationSystem;
		delete this->randomizer;
		delete this->currentTetromino;
	}
}
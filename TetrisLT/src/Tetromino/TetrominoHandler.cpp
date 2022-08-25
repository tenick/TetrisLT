#include "../../h/Tetromino/TetrominoHandler.hpp"
#include <iostream>

namespace Tetromino {
	TetrominoHandler::TetrominoHandler(std::vector<std::vector<TetrominoEnum>>& boardState, 
									   Randomizer::RandomizerBase* randomizer)
		: BoardState(boardState), randomizer(randomizer), currentTetromino(randomizer->Next()),
		  BoardHeight(boardState.size()), BoardWidth(boardState[0].size())
	{
	}

	void TetrominoHandler::Lock() {
		auto currentTetromino = this->GetCurrentTetromino();
		auto currentTetrominoState = currentTetromino->GetCurrentState();
		// add current tetromino to the board state
		for (int r = 0; r < currentTetromino->GetHeight(); r++) {
			for (int c = 0; c < currentTetromino->GetWidth(); c++) {
				int boardR = r + currentTetromino->GetRowOffset();
				int boardC = c + currentTetromino->GetColumnOffset();
				if (currentTetrominoState[r][c] != _)
					this->BoardState[boardR][boardC] = currentTetrominoState[r][c];
			}
		}
	}

	void TetrominoHandler::Update() {
	// update tetris states (time to get next piece? time to randomize? etc...)
	// TODO: lock delay w/ limit after resetting of lock delay due to move/rotation of piece
	// TODO: adding falling of tetromino via gameplay fall speed

	// handle keyboard
		static const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

		// harddrop input
		if (currentKeyStates[this->HardDrop])
		{
			if (!this->onHarddrop) {
				while (this->Move(M_D))
					continue;

				this->Lock();
				
				this->Next();
				this->onHarddrop = true;
				this->currentHold = 0;
			}
		}
		else
			this->onHarddrop = false;

		// softdrop input
		if (currentKeyStates[this->SoftDrop])
		{
			if (!this->SDSActivated) {
				this->Move(M_D);
				this->currentSDS = SDL_GetTicks64();
				this->SDSActivated = true;
			}
			else if (this->SDSActivated && SDL_GetTicks64() - this->currentSDS >= this->SDS) {
				this->Move(M_D);
				this->currentSDS = SDL_GetTicks64();
			}
		}
		else {
			this->SDSActivated = false;
			this->currentSDS = 0;
		}

		// hold tetromino
		if (currentKeyStates[this->HoldTetrominoKey]) {
			if (this->holdTetromino == nullptr) {
				this->holdTetromino = this->currentTetromino;
				this->currentTetromino = this->randomizer->Next();
				this->currentHold++;
			}
			else {
				if (this->currentHold < this->holdLimit) {
					auto temp = this->holdTetromino;
					this->holdTetromino = this->currentTetromino;
					this->currentTetromino = temp;
					this->currentHold++;
				}
			}
		}

		// rotation CW, CCW, and 180
		if (currentKeyStates[this->RotateCW]) {
			if (!this->onCWRotate) {
				this->Rotate(TetrominoRotationEnum::R_CW);
				this->onCWRotate = true;
			}
		}
		else
			this->onCWRotate = false;
		if (currentKeyStates[this->RotateCCW]) {
			if (!this->onCCWRotate) {
				this->Rotate(TetrominoRotationEnum::R_CCW);
				this->onCCWRotate = true;
			}
		}
		else
			this->onCCWRotate = false;
		if (currentKeyStates[this->Rotate180]) {
			if (!this->on180Rotate) {
				this->Rotate(TetrominoRotationEnum::R_180);
				this->on180Rotate = true;
			}
		}
		else
			this->on180Rotate = false;


		// move left
		if (currentKeyStates[this->MoveLeft])
		{
			if (!this->leftARRActivated) {
				if (!this->onLeftDAS) {
					this->Move(M_L);
					this->onLeftDAS = true;
					this->currentLeftDAS = SDL_GetTicks64();
				}
				else if (this->onLeftDAS && SDL_GetTicks64() - this->currentLeftDAS >= this->DAS) {
					this->leftARRActivated = true;
					this->currentLeftARR = SDL_GetTicks();
				}
			}
			else if (this->leftARRActivated && SDL_GetTicks64() - this->currentLeftARR >= this->ARR) {
				this->Move(M_L);
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
		if (currentKeyStates[this->MoveRight])
		{
			if (!this->rightARRActivated) {
				if (!this->onRightDAS) {
					this->Move(M_R);
					this->onRightDAS = true;
					this->currentRightDAS = SDL_GetTicks64();
				}
				else if (this->onRightDAS && SDL_GetTicks64() - this->currentRightDAS >= this->DAS) {
					this->rightARRActivated = true;
					this->currentRightARR = SDL_GetTicks();
				}
			}
			else if (this->rightARRActivated && SDL_GetTicks64() - this->currentRightARR >= this->ARR) {
				this->Move(M_R);
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
								  this->currentTetromino->GetCurrentState(),
								  this->currentTetromino->GetColumnOffset() - 1, 
								  this->currentTetromino->GetRowOffset());
				if (canMove)
					this->currentTetromino->SetColumnOffset(this->currentTetromino->GetColumnOffset() - 1);
				break;
			case M_R:
				canMove = CanMove(this->BoardState,
								  this->currentTetromino->GetCurrentState(),
								  this->currentTetromino->GetColumnOffset() + 1, 
								  this->currentTetromino->GetRowOffset());
				if (canMove)
					this->currentTetromino->SetColumnOffset(this->currentTetromino->GetColumnOffset() + 1);
				break;
			case M_D:
				canMove = CanMove(this->BoardState,
								  this->currentTetromino->GetCurrentState(),
								  this->currentTetromino->GetColumnOffset(), 
								  this->currentTetromino->GetRowOffset() + 1);
				if (canMove)
					this->currentTetromino->SetRowOffset(this->currentTetromino->GetRowOffset() + 1);
				break;
		}
		return canMove;
	}

	bool TetrominoHandler::Rotate(TetrominoRotationEnum rotateDir) {
		int resultingStateIndex = this->currentTetromino->GetCurrentStateIndex();
		switch (rotateDir) {
			case R_CW:
				resultingStateIndex++;
				break;
			case R_CCW:
				resultingStateIndex--;
				break;
			case R_180:
				resultingStateIndex += 2;
				break;
		}

		bool canMove = CanMove(this->BoardState,
							   this->currentTetromino->GetRotationStateAt(resultingStateIndex),
							   this->currentTetromino->GetColumnOffset(),
							   this->currentTetromino->GetRowOffset());
		if (canMove)
			this->currentTetromino->SetCurrentStateIndex(resultingStateIndex);
		return canMove;
	}

	void TetrominoHandler::Next() {
		delete this->currentTetromino;
		this->currentTetromino = this->randomizer->Next();
	}

	TetrominoBase* TetrominoHandler::GetHoldTetromino() {
		return this->holdTetromino;
	}

	TetrominoBase* TetrominoHandler::GetCurrentTetromino() {
		return this->currentTetromino;
	}

	const std::array<const TetrominoBase*, 5> TetrominoHandler::PeekNext5Tetrominos() {
		return this->randomizer->PeekNext5();
	}

	TetrominoHandler::~TetrominoHandler() {
		delete this->randomizer;
		delete this->currentTetromino;
		delete this->holdTetromino;
	}
}
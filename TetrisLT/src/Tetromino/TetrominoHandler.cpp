#include "../../h/Tetromino/TetrominoHandler.hpp"
#include <iostream>

namespace Tetromino {
	TetrominoHandler::TetrominoHandler(std::vector<std::vector<TetrominoEnum>>& boardState, 
									   Randomizer::RandomizerBase* randomizer)
		: BoardState(boardState), randomizer(randomizer), currentTetromino(randomizer->Next()),
		  BoardHeight(boardState.size()), BoardWidth(boardState[0].size())
	{
	}

	bool TetrominoHandler::canMove(const std::vector<std::vector<TetrominoEnum>>& tetrominoState, int newColOffset, int newRowOffset) {
		for (int c = 0; c < tetrominoState[0].size(); c++) {
			int boardC = newColOffset + c;
			for (int r = 0; r < tetrominoState.size(); r++) {
				int boardR = newRowOffset + r;

				if (boardC < 0 || boardC >= this->BoardWidth || boardR >= this->BoardHeight) { // means piece array is reaching outside of board
					// check if any piece is outside the board, can't move
					if (tetrominoState[r][c] != _)
						return false;
				}
				else { // means piece array is inside the board
					// check if any piece in array is touching any piece in board
					if (tetrominoState[r][c] != _ && this->BoardState[boardR][boardC] != _)
						return false;
				}
			}
		}
		return true;
	}

	bool TetrominoHandler::Move(TetrominoMoveEnum moveDir) {
		bool canMove = false;
		switch (moveDir) {
			case M_L:
				canMove = this->canMove(this->currentTetromino->GetCurrentState(),
										this->currentTetromino->GetColumnOffset() - 1, 
										this->currentTetromino->GetRowOffset());
				if (canMove)
					this->currentTetromino->SetColumnOffset(this->currentTetromino->GetColumnOffset() - 1);
				break;
			case M_R:
				canMove = this->canMove(this->currentTetromino->GetCurrentState(),
										this->currentTetromino->GetColumnOffset() + 1, 
										this->currentTetromino->GetRowOffset());
				if (canMove)
					this->currentTetromino->SetColumnOffset(this->currentTetromino->GetColumnOffset() + 1);
				break;
			case M_D:
				canMove = this->canMove(this->currentTetromino->GetCurrentState(),
										this->currentTetromino->GetColumnOffset(), 
										this->currentTetromino->GetRowOffset() + 1);
				if (canMove)
					this->currentTetromino->SetRowOffset(this->currentTetromino->GetRowOffset() + 1);
				break;
		}
		return canMove;
	}

	// TODO: ROTATE, and maybe Rotation system base class (child classes: SRS, classic, etc...)and Rotation folder
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

		bool canMove = this->canMove(this->currentTetromino->GetRotationStateAt(resultingStateIndex),
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

	void TetrominoHandler::HoldTetromino() {
		if (this->holdTetromino == nullptr) {
			this->holdTetromino = this->currentTetromino;
			this->currentTetromino = this->randomizer->Next();
		}
		else {
			auto temp = this->holdTetromino;
			this->holdTetromino = this->currentTetromino;
			this->currentTetromino = temp;
		}
	}

	std::array<TetrominoBase*, 5> TetrominoHandler::PeekNext5Tetrominos() {
		return this->randomizer->GetNext5();
	}

	TetrominoHandler::~TetrominoHandler() {
		delete this->randomizer;
	}
}
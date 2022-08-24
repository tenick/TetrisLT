#include "../../h/Tetromino/TetrominoBase.hpp"
#include "../../h/Tetromino/I.hpp"
#include "../../h/Tetromino/J.hpp"
#include "../../h/Tetromino/L.hpp"
#include "../../h/Tetromino/O.hpp"
#include "../../h/Tetromino/S.hpp"
#include "../../h/Tetromino/T.hpp"
#include "../../h/Tetromino/Z.hpp"

namespace Tetromino {
	TetrominoBase::TetrominoBase(std::vector<std::vector<std::vector<TetrominoEnum>>> rotationStates,
								 int initialRowOffset, int initialColumnOffset,
								 int initialRotationState) 
		: RotationStates(rotationStates), 
		  tetrominoHeight(rotationStates[0].size()), tetrominoWidth(rotationStates[0][0].size()),
		  rowOffset(initialRowOffset), columnOffset(initialColumnOffset),
		  currentRotationState(initialRotationState),
		  statesAmt(rotationStates.size())
	{
	}
	int TetrominoBase::GetRowOffset() { return this->rowOffset; };
	int TetrominoBase::GetColumnOffset() { return this->columnOffset; }
	void TetrominoBase::SetRowOffset(int newRowOffset) { this->rowOffset = newRowOffset; }
	void TetrominoBase::SetColumnOffset(int newColumnOffset) { this->columnOffset = newColumnOffset; }
	int TetrominoBase::GetWidth() { return this->tetrominoWidth; }
	int TetrominoBase::GetHeight() { return this->tetrominoHeight; }
	int TetrominoBase::GetCurrentStateIndex() { return this->currentRotationState; }
	void TetrominoBase::SetCurrentStateIndex(int newStateIndex) { this->currentRotationState = this->adjustStateIndex(newStateIndex); }
	const std::vector<std::vector<TetrominoEnum>>& TetrominoBase::GetCurrentState() { return this->RotationStates[this->currentRotationState]; }
	const std::vector<std::vector<TetrominoEnum>>& TetrominoBase::GetRotationStateAt(int index) {
		int actualIndex = this->adjustStateIndex(index);
		return this->RotationStates[actualIndex];
	}
	int TetrominoBase::adjustStateIndex(int index) {
		int actualIndex = index % this->statesAmt;
		if (actualIndex < 0) actualIndex += this->statesAmt;
		return actualIndex;
	}


	TetrominoBase* EnumToTetromino(TetrominoEnum tetrEnum) {
		switch (tetrEnum) {
			case I_:
				return new I;
			case J_:
				return new J;
			case L_:
				return new L;
			case O_:
				return new O;
			case S_:
				return new S;
			case T_:
				return new T;
			case Z_:
				return new Z;
			default:
				return nullptr;
		}
	}
}

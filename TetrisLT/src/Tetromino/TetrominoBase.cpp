#include "../../h/Tetromino/TetrominoBase.hpp"
#include "../../h/Tetromino/I.hpp"
#include "../../h/Tetromino/J.hpp"
#include "../../h/Tetromino/L.hpp"
#include "../../h/Tetromino/O.hpp"
#include "../../h/Tetromino/S.hpp"
#include "../../h/Tetromino/T.hpp"
#include "../../h/Tetromino/Z.hpp"

namespace Tetromino {
	TetrominoBase::TetrominoBase(int initialRowOffset, int initialColumnOffset,
								 int initialRotationState) 
		: RowOffset(initialRowOffset), ColumnOffset(initialColumnOffset),
		  CurrentRotationStateIndex(initialRotationState)
	{
	}

	int TetrominoBase::Height() const {
		return GetRotationStates()[0].size();
	}
	int TetrominoBase::Width() const {
		return GetRotationStates()[0][0].size();
	}
	const std::vector<std::vector<TetrominoEnum>>& TetrominoBase::GetCurrentRotationState() const {
		return this->GetRotationStates()[this->GetCurrentRotationStateIndex()];
	}
	const std::vector<std::vector<TetrominoEnum>>& TetrominoBase::GetRotationStateAt(int index) const {
		return this->GetRotationStates()[this->AdjustRotationStateIndex(index)];
	};
	int TetrominoBase::RotationStatesAmount() const {
		return this->GetRotationStates().size();
	}
	int TetrominoBase::GetCurrentRotationStateIndex() const {
		return this->CurrentRotationStateIndex;
	}
	void TetrominoBase::SetCurrentRotationStateIndex(int newStateIndex) {
		this->CurrentRotationStateIndex = this->AdjustRotationStateIndex(newStateIndex);
	}

	int TetrominoBase::AdjustRotationStateIndex(int stateIndex) const {
		int actualIndex = stateIndex % this->RotationStatesAmount();
		if (actualIndex < 0) actualIndex += this->RotationStatesAmount();
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
		}
	}
	void EnumToRGBA(TetrominoEnum tetrEnum, uint8_t& R, uint8_t& G, uint8_t& B, uint8_t& A) {
		switch (tetrEnum) {
		case I_:
			R = 0x00; G = 0xFF; B = 0xFF; A = 0xFF; break; // cyan
		case J_:
			R = 0x00; G = 0x00; B = 0xFF; A = 0xFF; break; // blue
		case L_:
			R = 0xFF; G = 0xA5; B = 0x00; A = 0xFF; break; // orange
		case O_:
			R = 0xFF; G = 0xFF; B = 0x00; A = 0xFF; break; // yellow
		case S_:
			R = 0x00; G = 0xFF; B = 0x00; A = 0xFF; break; // green
		case T_:
			R = 0xA0; G = 0x20; B = 0xF0; A = 0xFF; break; // purple
		case Z_:
			R = 0xFF; G = 0x00; B = 0x00; A = 0xFF; break; // red
		}
	}

	const std::vector<std::vector<std::vector<TetrominoEnum>>>& EnumToRotationStates(TetrominoEnum tetrEnum) {
		switch (tetrEnum) {
			case I_:
				return I::RotationStates;
			case J_:
				return J::RotationStates;
			case L_:
				return L::RotationStates;
			case O_:
				return O::RotationStates;
			case S_:
				return S::RotationStates;
			case T_:
				return T::RotationStates;
			case Z_:
				return Z::RotationStates;
		}
	}


	bool CanMove(const std::vector<std::vector<TetrominoEnum>>& boardState, const std::vector<std::vector<TetrominoEnum>>& tetrominoState, int newColOffset, int newRowOffset) {
		int boardHeight = boardState.size();
		int boardWidth = boardState[0].size();
		for (int c = 0; c < tetrominoState[0].size(); c++) {
			int boardC = newColOffset + c;
			for (int r = 0; r < tetrominoState.size(); r++) {
				int boardR = newRowOffset + r;

				if (boardC < 0 || boardC >= boardWidth || boardR >= boardHeight) { // means piece array is reaching outside of board
					// check if any piece is outside the board, can't move
					if (tetrominoState[r][c] != _)
						return false;
				}
				else { // means piece array is inside the board
					// check if any piece in array is touching any piece in board
					if (tetrominoState[r][c] != _ && boardState[boardR][boardC] != _)
						return false;
				}
			}
		}
		return true;
	}

}

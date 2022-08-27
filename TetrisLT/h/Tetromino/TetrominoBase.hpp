#pragma once
#include <vector>

namespace Tetromino {
	enum TetrominoEnum {
		_, I_, J_, L_, O_, S_, T_, Z_
	};

	enum TetrominoRotationEnum {
		R_CW, R_CCW, R_180
	};

	enum TetrominoMoveEnum {
		M_L, M_R, M_D
	};

	class TetrominoBase {
	public:
		virtual TetrominoEnum GetTetrominoEnumEquivalent() const = 0;
		virtual const std::vector<std::vector<std::vector<TetrominoEnum>>>& GetRotationStates() const = 0;
		
		int Height() const;
		int Width() const;
		const std::vector<std::vector<TetrominoEnum>>& GetCurrentRotationState() const;
		const std::vector<std::vector<TetrominoEnum>>& GetRotationStateAt(int index) const;
		int RotationStatesAmount() const;
		int GetCurrentRotationStateIndex() const;
		void SetCurrentRotationStateIndex(int newStateIndex);

		int RowOffset;
		int ColumnOffset;
	protected:
		int AdjustRotationStateIndex(int stateIndex) const;
		TetrominoBase(int startingRowOffset = 0, int startingColumnOffset = 3,
					  int initialState = 0);
		
		int CurrentRotationStateIndex;
	};
	

	/*  H E L P E R S  */
	TetrominoBase* EnumToTetromino(TetrominoEnum tetrEnum);
	void EnumToRGBA(TetrominoEnum tetrEnum, uint8_t& R, uint8_t& G, uint8_t& B, uint8_t& A);
	const std::vector<std::vector<std::vector<TetrominoEnum>>>& EnumToRotationStates(TetrominoEnum tetrEnum);
	bool CanMove(const std::vector<std::vector<TetrominoEnum>>& boardState, const std::vector<std::vector<TetrominoEnum>>& tetrominoState, int newColOffset, int newRowOffset);
}
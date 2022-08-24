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
		int GetRowOffset();
		int GetColumnOffset();
		void SetRowOffset(int newRowOffset);
		void SetColumnOffset(int newColumnOffset);
		int GetWidth();
		int GetHeight();
		int GetCurrentStateIndex();
		void SetCurrentStateIndex(int newStateIndex);
		const std::vector<std::vector<TetrominoEnum>>& GetCurrentState();
		const std::vector<std::vector<TetrominoEnum>>& GetRotationStateAt(int index);
	protected:
		TetrominoBase(std::vector<std::vector<std::vector<TetrominoEnum>>> rotationStates,
					  int startingRowOffset = 0, int startingColumnOffset = 4,
					  int initialState = 0);
		const std::vector<std::vector<std::vector<TetrominoEnum>>> RotationStates;
		const int tetrominoHeight;
		const int tetrominoWidth;
		int rowOffset;
		int columnOffset;
		int currentRotationState;
		const int statesAmt;
	private:
		int adjustStateIndex(int index);
	};
	
	TetrominoBase* EnumToTetromino(TetrominoEnum tetrEnum);

}
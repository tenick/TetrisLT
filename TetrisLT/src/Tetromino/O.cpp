#include "../../h/Tetromino/O.hpp"

namespace Tetromino {
	O::O(int startingRowOffset, int startingColumnOffset,
		 int initialState)
		: TetrominoBase(startingRowOffset, startingColumnOffset, initialState)
	{
	}

	TetrominoEnum O::GetTetrominoEnumEquivalent() const {
		return O::TetrominoEnumEquivalent;
	}
	const std::vector<std::vector<std::vector<TetrominoEnum>>>& O::GetRotationStates() const {
		return O::RotationStates;
	};

	const TetrominoEnum O::TetrominoEnumEquivalent(O_);
	const std::vector<std::vector<std::vector<TetrominoEnum>>> O::RotationStates(
		{ {
			{
				{{_, O_, O_, _},
				 {_, O_, O_, _},
				 {_, _ , _ , _}}
			}
		} }
	);
}

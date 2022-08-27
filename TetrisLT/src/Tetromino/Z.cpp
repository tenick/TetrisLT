#include "../../h/Tetromino/Z.hpp"

namespace Tetromino {
	Z::Z(int startingRowOffset, int startingColumnOffset,
		 int initialState)
		: TetrominoBase(startingRowOffset, startingColumnOffset, initialState)
	{
	}

	TetrominoEnum Z::GetTetrominoEnumEquivalent() const {
		return Z::TetrominoEnumEquivalent;
	}
	const std::vector<std::vector<std::vector<TetrominoEnum>>>& Z::GetRotationStates() const {
		return Z::RotationStates;
	};

	const TetrominoEnum Z::TetrominoEnumEquivalent(Z_);
	const std::vector<std::vector<std::vector<TetrominoEnum>>> Z::RotationStates(
		{ {
			{
				{{Z_, Z_, _ },
				 {_ , Z_, Z_},
				 {_ , _ , _ }}
			},
			{
				{{_ , _ , Z_},
				 {_ , Z_, Z_},
				 {_ , Z_, _ }}
			},
			{
				{{_ , _ , _ },
				 {Z_, Z_, _ },
				 {_ , Z_, Z_}}
			},
			{
				{{_ , Z_, _ },
				 {Z_, Z_, _ },
				 {Z_, _ , _ }}
			}
		} }
	);
}

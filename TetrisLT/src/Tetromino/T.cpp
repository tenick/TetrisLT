#include "../../h/Tetromino/T.hpp"

namespace Tetromino {
	T::T(int startingRowOffset, int startingColumnOffset,
		 int initialState)
		: TetrominoBase(startingRowOffset, startingColumnOffset, initialState)
	{
	}

	TetrominoEnum T::GetTetrominoEnumEquivalent() const {
		return T::TetrominoEnumEquivalent;
	}
	const std::vector<std::vector<std::vector<TetrominoEnum>>>& T::GetRotationStates() const {
		return T::RotationStates;
	};

	const TetrominoEnum T::TetrominoEnumEquivalent(T_);
	const std::vector<std::vector<std::vector<TetrominoEnum>>> T::RotationStates(
		{ {
			{
				{{_ , T_, _ },
				 {T_, T_, T_},
				 {_ , _ , _ }}
			},
			{
				{{_ , T_, _ },
				 {_ , T_, T_},
				 {_ , T_, _ }}
			},
			{
				{{_ , _ , _ },
				 {T_, T_, T_},
				 {_ , T_, _ }}
			},
			{
				{{_ , T_, _ },
				 {T_, T_, _ },
				 {_ , T_, _ }}
			}
		} }
	);
}

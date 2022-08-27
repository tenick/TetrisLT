#include "../../h/Tetromino/S.hpp"

namespace Tetromino {
	S::S(int startingRowOffset, int startingColumnOffset,
		 int initialState)
		: TetrominoBase(startingRowOffset, startingColumnOffset, initialState)
	{
	}

	TetrominoEnum S::GetTetrominoEnumEquivalent() const {
		return S::TetrominoEnumEquivalent;
	}
	const std::vector<std::vector<std::vector<TetrominoEnum>>>& S::GetRotationStates() const {
		return S::RotationStates;
	};

	const TetrominoEnum S::TetrominoEnumEquivalent(S_);
	const std::vector<std::vector<std::vector<TetrominoEnum>>> S::RotationStates(
		{ {
			{
				{{_ , S_, S_},
				 {S_, S_, _ },
				 {_ , _ , _ }}
			},
			{
				{{_ , S_, _ },
				 {_ , S_, S_},
				 {_ , _ , S_}}
			},
			{
				{{_ , _ , _ },
				 {_ , S_, S_},
				 {S_, S_, _ }}
			},
			{
				{{S_, _ , _ },
				 {S_, S_, _ },
				 {_ , S_, _ }}
			}
		} }
	);
}

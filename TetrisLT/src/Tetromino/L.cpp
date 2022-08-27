#include "../../h/Tetromino/L.hpp"

namespace Tetromino {
	L::L(int startingRowOffset, int startingColumnOffset,
		int initialState)
		: TetrominoBase(startingRowOffset, startingColumnOffset, initialState)
	{
	}

	TetrominoEnum L::GetTetrominoEnumEquivalent() const {
		return L::TetrominoEnumEquivalent;
	}
	const std::vector<std::vector<std::vector<TetrominoEnum>>>& L::GetRotationStates() const {
		return L::RotationStates;
	};

	const TetrominoEnum L::TetrominoEnumEquivalent(L_);
	const std::vector<std::vector<std::vector<TetrominoEnum>>> L::RotationStates(
		{ {
			{
				{{_ , _ , L_},
				 {L_, L_, L_},
				 {_ , _ , _ }}
			},
			{
				{{_ , L_, _ },
				 {_ , L_, _ },
				 {_ , L_, L_}}
			},
			{
				{{_ , _ , _ },
				 {L_, L_, L_},
				 {L_ , _ , _ }}
			},
			{
				{{L_, L_, _ },
				 {_ , L_, _ },
				 {_ , L_, _ }}
			}
		} }
	);
}

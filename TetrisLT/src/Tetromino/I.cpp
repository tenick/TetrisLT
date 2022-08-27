#include "../../h/Tetromino/I.hpp"

namespace Tetromino {
	I::I(int startingRowOffset, int startingColumnOffset,
		 int initialState)
		: TetrominoBase(startingRowOffset, startingColumnOffset, initialState)
	{
	}

	TetrominoEnum I::GetTetrominoEnumEquivalent() const {
		return I::TetrominoEnumEquivalent;
	}
	const std::vector<std::vector<std::vector<TetrominoEnum>>>& I::GetRotationStates() const {
		return I::RotationStates;
	};

	const TetrominoEnum I::TetrominoEnumEquivalent(I_);
	const std::vector<std::vector<std::vector<TetrominoEnum>>> I::RotationStates(
		{ {
			{
				{{_ , _ , _ , _ },
				 {I_, I_, I_, I_},
				 {_ , _ , _ , _ },
				 {_ , _ , _ , _ }},
			},
			{
				{{_ , _ , I_, _ },
				 {_ , _ , I_, _ },
				 {_ , _ , I_, _ },
				 {_ , _ , I_, _ }},
			},
			{
				{{_ , _ , _ , _ },
				 {_ , _ , _ , _ },
				 {I_, I_, I_, I_},
				 {_ , _ , _ , _ }},
			},
			{
				{{_ , I_, _ , _ },
				 {_ , I_, _ , _ },
				 {_ , I_, _ , _ },
				 {_ , I_, _ , _ }},
			}
		} }
	);
}

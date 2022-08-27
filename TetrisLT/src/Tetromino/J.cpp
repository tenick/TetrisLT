#include "../../h/Tetromino/J.hpp"

namespace Tetromino {
	J::J(int startingRowOffset, int startingColumnOffset,
		int initialState)
		: TetrominoBase(startingRowOffset, startingColumnOffset, initialState)
	{
	}

	TetrominoEnum J::GetTetrominoEnumEquivalent() const {
		return J::TetrominoEnumEquivalent;
	}
	const std::vector<std::vector<std::vector<TetrominoEnum>>>& J::GetRotationStates() const {
		return J::RotationStates;
	};

	const TetrominoEnum J::TetrominoEnumEquivalent(J_);
	const std::vector<std::vector<std::vector<TetrominoEnum>>> J::RotationStates(
		{ {
			{
				{{J_, _ , _ },
				 {J_, J_, J_},
				 {_ , _ , _ }}
			},
			{
				{{_ , J_, J_},
				 {_ , J_, _ },
				 {_ , J_, _ }}
			},
			{
				{{_ , _ , _ },
				 {J_, J_, J_},
				 {_ , _ , J_}}
			},
			{
				{{_ , J_, _ },
				 {_ , J_, _ },
				 {J_, J_, _ }}
			}
		} }
	);
}

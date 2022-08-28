#include "../../h/Tetromino/J.hpp"

namespace Tetromino {
	J::J(RotationSystem::RotationSystemBase*& rsBase, 
		 int startingRowOffset, int startingColumnOffset,
		 int initialState)
		: TetrominoBase(rsBase, startingRowOffset, startingColumnOffset, initialState)
	{
	}

	TetrominoEnum J::GetTetrominoEnumEquivalent() const {
		return J::TetrominoEnumEquivalent;
	}
	const std::vector<std::vector<std::vector<TetrominoEnum>>>& J::GetRotationStates() const {
		return this->rotationSystem->GetTetrominoRotationStates().at(this->GetTetrominoEnumEquivalent());
	};

	const TetrominoEnum J::TetrominoEnumEquivalent(J_);
}

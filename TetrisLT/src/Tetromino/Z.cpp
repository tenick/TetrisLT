#include "../../h/Tetromino/Z.hpp"

namespace Tetromino {
	Z::Z(RotationSystem::RotationSystemBase*& rsBase,
		 int startingRowOffset, int startingColumnOffset,
		 int initialState)
		: TetrominoBase(rsBase, startingRowOffset, startingColumnOffset, initialState)
	{
	}

	TetrominoEnum Z::GetTetrominoEnumEquivalent() const {
		return Z::TetrominoEnumEquivalent;
	}
	const std::vector<std::vector<std::vector<TetrominoEnum>>>& Z::GetRotationStates() const {
		return this->rotationSystem->GetTetrominoRotationStates().at(this->GetTetrominoEnumEquivalent());
	};

	const TetrominoEnum Z::TetrominoEnumEquivalent(Z_);
}

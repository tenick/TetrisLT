#include "../../h/Tetromino/I.hpp"

namespace Tetromino {
	I::I(RotationSystem::RotationSystemBase*& rsBase,
		 int startingRowOffset, int startingColumnOffset,
		 int initialState)
		: TetrominoBase(rsBase, startingRowOffset, startingColumnOffset, initialState)
	{
	}

	TetrominoEnum I::GetTetrominoEnumEquivalent() const {
		return I::TetrominoEnumEquivalent;
	}
	const std::vector<std::vector<std::vector<TetrominoEnum>>>& I::GetRotationStates() const {
		return this->rotationSystem->GetTetrominoRotationStates().at(this->GetTetrominoEnumEquivalent());
	};

	const TetrominoEnum I::TetrominoEnumEquivalent(I_);
}

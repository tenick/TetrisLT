#include "../../h/Tetromino/O.hpp"

namespace Tetromino {
	O::O(RotationSystem::RotationSystemBase*& rsBase, 
		 int startingRowOffset, int startingColumnOffset,
		 int initialState)
		: TetrominoBase(rsBase, startingRowOffset, startingColumnOffset, initialState)
	{
	}

	TetrominoEnum O::GetTetrominoEnumEquivalent() const {
		return O::TetrominoEnumEquivalent;
	}
	const std::vector<std::vector<std::vector<TetrominoEnum>>>& O::GetRotationStates() const {
		return this->rotationSystem->GetTetrominoRotationStates().at(this->GetTetrominoEnumEquivalent());
	};

	const TetrominoEnum O::TetrominoEnumEquivalent(O_);
}

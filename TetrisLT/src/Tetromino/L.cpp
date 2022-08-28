#include "../../h/Tetromino/L.hpp"

namespace Tetromino {
	L::L(RotationSystem::RotationSystemBase*& rsBase, 
		 int startingRowOffset, int startingColumnOffset,
		 int initialState)
		: TetrominoBase(rsBase, startingRowOffset, startingColumnOffset, initialState)
	{
	}

	TetrominoEnum L::GetTetrominoEnumEquivalent() const {
		return L::TetrominoEnumEquivalent;
	}
	const std::vector<std::vector<std::vector<TetrominoEnum>>>& L::GetRotationStates() const {
		return this->rotationSystem->GetTetrominoRotationStates().at(this->GetTetrominoEnumEquivalent());
	};

	const TetrominoEnum L::TetrominoEnumEquivalent(L_);
}

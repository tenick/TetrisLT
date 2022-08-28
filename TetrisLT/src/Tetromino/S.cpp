#include "../../h/Tetromino/S.hpp"

namespace Tetromino {
	S::S(RotationSystem::RotationSystemBase*& rsBase, 
		 int startingRowOffset, int startingColumnOffset,
		 int initialState)
		: TetrominoBase(rsBase, startingRowOffset, startingColumnOffset, initialState)
	{
	}

	TetrominoEnum S::GetTetrominoEnumEquivalent() const {
		return S::TetrominoEnumEquivalent;
	}
	const std::vector<std::vector<std::vector<TetrominoEnum>>>& S::GetRotationStates() const {
		return this->rotationSystem->GetTetrominoRotationStates().at(this->GetTetrominoEnumEquivalent());
	};

	const TetrominoEnum S::TetrominoEnumEquivalent(S_);
}

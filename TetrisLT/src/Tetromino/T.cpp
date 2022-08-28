#include "../../h/Tetromino/T.hpp"

namespace Tetromino {
	T::T(RotationSystem::RotationSystemBase*& rsBase, 
		 int startingRowOffset, int startingColumnOffset,
		 int initialState)
		: TetrominoBase(rsBase, startingRowOffset, startingColumnOffset, initialState)
	{
	}

	TetrominoEnum T::GetTetrominoEnumEquivalent() const {
		return T::TetrominoEnumEquivalent;
	}
	const std::vector<std::vector<std::vector<TetrominoEnum>>>& T::GetRotationStates() const {
		return this->rotationSystem->GetTetrominoRotationStates().at(this->GetTetrominoEnumEquivalent());
	};

	const TetrominoEnum T::TetrominoEnumEquivalent(T_);
}

#include "../../h/Tetromino/TetrominoBase.hpp"

#include "../../h/RotationSystem/RotationSystemBase.hpp"

namespace Tetromino {
	TetrominoBase::TetrominoBase(RotationSystem::RotationSystemBase*& rsBase,
								 int initialRowOffset, int initialColumnOffset,
								 int initialRotationState)
		: rotationSystem(rsBase),
		  RowOffset(initialRowOffset), ColumnOffset(initialColumnOffset),
		  CurrentRotationStateIndex(initialRotationState)
	{
	}

	int TetrominoBase::Height() const {
		return GetRotationStates()[0].size();
	}
	int TetrominoBase::Width() const {
		return GetRotationStates()[0][0].size();
	}
	const std::vector<std::vector<TetrominoEnum>>& TetrominoBase::GetCurrentRotationState() const {
		return this->GetRotationStates()[this->GetCurrentRotationStateIndex()];
	}
	const std::vector<std::vector<TetrominoEnum>>& TetrominoBase::GetRotationStateAt(int index) const {
		return this->GetRotationStates()[this->AdjustRotationStateIndex(index)];
	};
	int TetrominoBase::RotationStatesAmount() const {
		return this->GetRotationStates().size();
	}
	int TetrominoBase::GetCurrentRotationStateIndex() const {
		return this->CurrentRotationStateIndex;
	}
	void TetrominoBase::SetCurrentRotationStateIndex(int newStateIndex) {
		this->CurrentRotationStateIndex = this->AdjustRotationStateIndex(newStateIndex);
	}

	int TetrominoBase::AdjustRotationStateIndex(int stateIndex) const {
		int actualIndex = stateIndex % this->RotationStatesAmount();
		if (actualIndex < 0) actualIndex += this->RotationStatesAmount();
		return actualIndex;
	}
}

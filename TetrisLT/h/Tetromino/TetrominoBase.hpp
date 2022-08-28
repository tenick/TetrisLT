#ifndef TETROMINO_BASE_H
#define TETROMINO_BASE_H

#include "TetrominoEnum.hpp"
#include <vector>

namespace RotationSystem{
	class RotationSystemBase;
}

namespace Tetromino {

	class TetrominoBase {
	public:
		virtual TetrominoEnum GetTetrominoEnumEquivalent() const = 0;
		virtual const std::vector<std::vector<std::vector<TetrominoEnum>>>& GetRotationStates() const = 0;

		int Height() const;
		int Width() const;
		const std::vector<std::vector<TetrominoEnum>>& GetCurrentRotationState() const;
		const std::vector<std::vector<TetrominoEnum>>& GetRotationStateAt(int index) const;
		int RotationStatesAmount() const;
		int GetCurrentRotationStateIndex() const;
		void SetCurrentRotationStateIndex(int newStateIndex);

		int RowOffset;
		int ColumnOffset;
		int AdjustRotationStateIndex(int stateIndex) const;
	protected:
		TetrominoBase(RotationSystem::RotationSystemBase*& rsBase,
					  int startingRowOffset = 0, int startingColumnOffset = 3,
					  int initialState = 0);
		
		int CurrentRotationStateIndex;
		RotationSystem::RotationSystemBase*& rotationSystem;
	};
}

#endif
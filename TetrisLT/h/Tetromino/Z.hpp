#ifndef Z_H
#define Z_H

#include "TetrominoBase.hpp"
#include "../RotationSystem/RotationSystemBase.hpp"

namespace Tetromino {
	class Z : public TetrominoBase {
	public:
		Z(RotationSystem::RotationSystemBase*& rsBase,
		  int startingRowOffset = 0, int startingColumnOffset = 3,
		  int initialState = 0);

		virtual TetrominoEnum GetTetrominoEnumEquivalent() const override;
		virtual const std::vector<std::vector<std::vector<TetrominoEnum>>>& GetRotationStates() const override;

		const static TetrominoEnum TetrominoEnumEquivalent;
	};
}

#endif
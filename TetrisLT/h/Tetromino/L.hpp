#ifndef L_H
#define L_H

#include "TetrominoBase.hpp"
#include "../RotationSystem/RotationSystemBase.hpp"

namespace Tetromino {
	class L : public TetrominoBase {
	public:
		L(RotationSystem::RotationSystemBase*& rsBase,
		  int startingRowOffset = 0, int startingColumnOffset = 3,
		  int initialState = 0);

		virtual TetrominoEnum GetTetrominoEnumEquivalent() const override;
		virtual const std::vector<std::vector<std::vector<TetrominoEnum>>>& GetRotationStates() const override;

		const static TetrominoEnum TetrominoEnumEquivalent;
	};
}

#endif
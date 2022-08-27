#pragma once
#include "TetrominoBase.hpp"

namespace Tetromino {
	class I : public TetrominoBase {
	public:
		I(int startingRowOffset = 0, int startingColumnOffset = 3,
		  int initialState = 0);

		virtual TetrominoEnum GetTetrominoEnumEquivalent() const override;
		virtual const std::vector<std::vector<std::vector<TetrominoEnum>>>& GetRotationStates() const override;

		const static TetrominoEnum TetrominoEnumEquivalent;
		const static std::vector<std::vector<std::vector<TetrominoEnum>>> RotationStates;
	};
}
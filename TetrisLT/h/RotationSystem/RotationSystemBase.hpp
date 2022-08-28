#ifndef ROTATION_SYSTEM_BASE_H
#define ROTATION_SYSTEM_BASE_H

#include "RotationSystemEnum.hpp"
#include "../Tetromino/TetrominoEnum.hpp"
#include "../Tetromino/TetrominoBase.hpp"
#include "../Tetromino/TetrominoRotationEnum.hpp"

#include <unordered_map>
#include <vector>

using namespace Tetromino;

namespace RotationSystem {
	class RotationSystemBase {
	public:
		virtual RotationSystemEnum GetRotationSystemEnumEquivalent() const = 0;
		virtual const std::unordered_map<TetrominoEnum,
			std::vector<std::vector<std::vector<TetrominoEnum>>>>& GetTetrominoRotationStates() const = 0;
		virtual bool Rotate(const std::vector<std::vector<TetrominoEnum>>& BoardState, TetrominoBase* tetromino, TetrominoRotationEnum rotateDir) const = 0;

	protected:
		int GetResultingRotationStateIndex(TetrominoBase* tetromino, TetrominoRotationEnum rotateDir) const;
	};

}

#endif
#ifndef ORIGINAL_H
#define ORIGINAL_H

#include "../Tetromino/TetrominoEnum.hpp"
#include "../Tetromino/TetrominoBase.hpp"
#include "../Tetromino/TetrominoRotationEnum.hpp"
#include "RotationSystemBase.hpp"

using namespace Tetromino;

namespace RotationSystem {
	class Original : public RotationSystemBase {
	public:
		virtual RotationSystemEnum GetRotationSystemEnumEquivalent() const override;
		virtual const std::unordered_map<TetrominoEnum,
			std::vector<std::vector<std::vector<TetrominoEnum>>>>&GetTetrominoRotationStates() const override;
		virtual bool Rotate(const std::vector<std::vector<TetrominoEnum>>& BoardState, TetrominoBase* tetromino, TetrominoRotationEnum rotateDir) const override;

		static const RotationSystemEnum RotationSystemEnumEquivalent;
		const static std::unordered_map<TetrominoEnum,
			std::vector<std::vector<std::vector<TetrominoEnum>>>> TetrominoRotationStates;
	};
}

#endif
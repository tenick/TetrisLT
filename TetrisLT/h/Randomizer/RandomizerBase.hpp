#pragma once
#include <array>
#include "../Tetromino/TetrominoBase.hpp"

using namespace Tetromino;
namespace Randomizer {
	class RandomizerBase {
	public:
		RandomizerBase();
		virtual TetrominoBase* Next() = 0;
		virtual const std::array<const TetrominoBase*, 5>& PeekNext5() = 0;
		void SetSeed(int seed);
	protected:
		int seed = 0;
	};
}
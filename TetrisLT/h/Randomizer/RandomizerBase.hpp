#ifndef RANDOMIZER_BASE_H
#define RANDOMIZER_BASE_H

#include "../Tetromino/TetrominoEnum.hpp"

#include <array>
#include <random>

using namespace Tetromino;

namespace Randomizer {
	class RandomizerBase {
	public:
		RandomizerBase();
		virtual TetrominoEnum Next() = 0;
		virtual const std::array<TetrominoEnum, 5> PeekNext5() = 0;
		void SetSeed(int seed);
	protected:
		int seed = 0;
		std::minstd_rand RNG;
	};
}

#endif
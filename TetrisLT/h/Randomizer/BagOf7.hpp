#ifndef BAG_OF_7_H
#define BAG_OF_7_H

#include "RandomizerBase.hpp"
#include <queue>

namespace Randomizer {
	class BagOf7 : public RandomizerBase {
	public:
		BagOf7();
		TetrominoEnum Next() override;
		const std::array<TetrominoEnum, 5> PeekNext5() override;
		void Reset() override;
	private:
		void refillQueue();

		std::array<Tetromino::TetrominoEnum, 7> bag = { I_, J_, L_, O_, S_, T_, Z_ };
		std::queue<TetrominoEnum> tetrominoQueue;
	};
}

#endif
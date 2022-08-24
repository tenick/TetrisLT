#pragma once
#include "RandomizerBase.hpp"
#include <queue>

namespace Randomizer {
	class BagOf7 : public RandomizerBase {
	public:
		BagOf7();
		TetrominoBase* Next() override;
		std::array<TetrominoBase*, 5> GetNext5() override;
	private:
		void refillQueue();

		Tetromino::TetrominoEnum bag[7] = { I_, J_, L_, O_, S_, T_, Z_ };
		std::queue<TetrominoBase*> tetrominoQueue;
	};
}

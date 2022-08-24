#include "../../h/Randomizer/BagOf7.hpp"

namespace Randomizer {
	BagOf7::BagOf7() {
		this->refillQueue();
	}

	TetrominoBase* BagOf7::Next() {
		auto front = this->tetrominoQueue.front();
		this->tetrominoQueue.pop();

		if (this->tetrominoQueue.size() < 5)
			this->refillQueue();

		return front;
	}

	std::array<TetrominoBase*, 5> BagOf7::GetNext5() {
		auto queueCopy = this->tetrominoQueue;
		std::array<TetrominoBase*, 5> arr;
		for (int i = 0; i < 5; i++) {
			arr[i] = queueCopy.front();
			queueCopy.pop();
		}
		return arr;
	}

	// TODO: calling EnumToTetromino might cause memory leak, because it's returning a new heap allocation, must delete that
	void BagOf7::refillQueue() {
		std::random_shuffle(std::begin(this->bag), std::end(this->bag));
		for (TetrominoEnum tetrEnum : this->bag)
			tetrominoQueue.push(EnumToTetromino(tetrEnum));
	}
}
#include "../../h/Randomizer/BagOf7.hpp"

namespace Randomizer {
	BagOf7::BagOf7() {
		this->refillQueue();
	}

	TetrominoEnum BagOf7::Next() {
		auto front = this->tetrominoQueue.front();
		this->tetrominoQueue.pop();

		if (this->tetrominoQueue.size() < 5)
			this->refillQueue();

		return front;
	}

	const std::array<TetrominoEnum, 5> BagOf7::PeekNext5() {
		std::queue<TetrominoEnum> queueCopy = this->tetrominoQueue;
		std::array<TetrominoEnum, 5> arr;
		for (int i = 0; i < 5; i++) {
			arr[i] = queueCopy.front();
			queueCopy.pop();
		}
		return arr;
	}

	// TODO: calling EnumToTetromino might cause memory leak, because it's returning a new heap allocation, must delete that
	void BagOf7::refillQueue() {
		std::shuffle(std::begin(this->bag), std::end(this->bag), this->RNG);
		for (TetrominoEnum tetrEnum : this->bag)
			tetrominoQueue.push(tetrEnum);
	}
}
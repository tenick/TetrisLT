#include "../../h/Tetromino/O.hpp"

namespace Tetromino {

	O::O() : TetrominoBase(
		std::vector<std::vector<std::vector<TetrominoEnum>>>(
		{ {
			{
				{{_, O_, O_, _},
				 {_, O_, O_, _},
				 {_, _ , _ , _}}
			}
		} }
	))
	{
	}
}

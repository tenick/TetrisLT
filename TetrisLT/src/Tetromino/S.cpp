#include "../../h/Tetromino/S.hpp"

namespace Tetromino {

	S::S() : TetrominoBase(
		std::vector<std::vector<std::vector<TetrominoEnum>>>(
		{ {
			{
				{{_ , S_, S_},
				 {S_, S_, _ },
				 {_ , _ , _ }}
			},
			{
				{{_ , S_, _ },
				 {_ , S_, S_},
				 {_ , _ , S_}}
			},
			{
				{{_ , _ , _ },
				 {_ , S_, S_},
				 {S_, S_, _ }}
			},
			{
				{{S_, _ , _ },
				 {S_, S_, _ },
				 {_ , S_, _ }}
			}
		} }
	))
	{
	}
}

#include "../../h/Tetromino/Z.hpp"

namespace Tetromino {
	Z::Z() : TetrominoBase(
		std::vector<std::vector<std::vector<TetrominoEnum>>>(
		{ {
			{
				{{Z_, Z_, _ },
				 {_ , Z_, Z_},
				 {_ , _ , _ }}
			},
			{
				{{_ , _ , Z_},
				 {_ , Z_, Z_},
				 {_ , Z_, _ }}
			},
			{
				{{_ , _ , _ },
				 {Z_, Z_, _ },
				 {_ , Z_, Z_}}
			},
			{
				{{_ , Z_, _ },
				 {Z_, Z_, _ },
				 {Z_, _ , _ }}
			}
		} }
		),
		Z_
	)
	{
	}
}

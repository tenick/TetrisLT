#include "../../h/Tetromino/T.hpp"

namespace Tetromino {
	T::T() : TetrominoBase(
		std::vector<std::vector<std::vector<TetrominoEnum>>>(
		{ {
			{
				{{_ , T_, _ },
				 {T_, T_, T_},
				 {_ , _ , _ }}
			},
			{
				{{_ , T_, _ },
				 {_ , T_, T_},
				 {_ , T_, _ }}
			},
			{
				{{_ , _ , _ },
				 {T_, T_, T_},
				 {_ , T_, _ }}
			},
			{
				{{_ , T_, _ },
				 {T_, T_, _ },
				 {_ , T_, _ }}
			}
		} }
		),
		T_
	)
	{
	}
}

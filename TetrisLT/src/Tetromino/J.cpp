#include "../../h/Tetromino/J.hpp"

namespace Tetromino {
	J::J() : TetrominoBase(
		std::vector<std::vector<std::vector<TetrominoEnum>>>(
		{ {
			{
				{{J_, _ , _ },
				 {J_, J_, J_},
				 {_ , _ , _ }}
			},
			{
				{{_ , J_, J_},
				 {_ , J_, _ },
				 {_ , J_, _ }}
			},
			{
				{{_ , _ , _ },
				 {J_, J_, J_},
				 {_ , _ , J_}}
			},
			{
				{{_ , J_, _ },
				 {_ , J_, _ },
				 {J_, J_, _ }}
			}
		} }
	))
	{
	}
}

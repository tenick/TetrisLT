#include "../../h/Tetromino/I.hpp"

namespace Tetromino {
	I::I() : TetrominoBase(
		std::vector<std::vector<std::vector<TetrominoEnum>>>(
		{ {
			{
				{{_ , _ , _ , _ },
				 {I_, I_, I_, I_},
				 {_ , _ , _ , _ },
				 {_ , _ , _ , _ }},
			},
			{
				{{_ , _ , I_, _ },
				 {_ , _ , I_, _ },
				 {_ , _ , I_, _ },
				 {_ , _ , I_, _ }},
			},
			{
				{{_ , _ , _ , _ },
				 {_ , _ , _ , _ },
				 {I_, I_, I_, I_},
				 {_ , _ , _ , _ }},
			},
			{
				{{_ , I_, _ , _ },
				 {_ , I_, _ , _ },
				 {_ , I_, _ , _ },
				 {_ , I_, _ , _ }},
			}
		} }
	))
	{
	}
}

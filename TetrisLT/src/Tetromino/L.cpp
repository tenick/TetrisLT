#include "../../h/Tetromino/L.hpp"

namespace Tetromino {
	L::L() : TetrominoBase(
		std::vector<std::vector<std::vector<TetrominoEnum>>>(
		{ {
			{
				{{_ , _ , L_},
				 {L_, L_, L_},
				 {_ , _ , _ }}
			},
			{
				{{_ , L_, _ },
				 {_ , L_, _ },
				 {_ , L_, L_}}
			},
			{
				{{_ , _ , _ },
				 {L_, L_, L_},
				 {L_ , _ , _ }}
			},
			{
				{{L_, L_, _ },
				 {_ , L_, _ },
				 {_ , L_, _ }}
			}
		} }
		),
		L_
	)
	{
	}
}

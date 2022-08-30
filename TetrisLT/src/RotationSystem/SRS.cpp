#include "../../h/RotationSystem/SRS.hpp"

#include "../../h/Tetromino/TetrominoEnum.hpp"
#include "../../h/Tetromino/TetrominoBase.hpp"
#include "../../h/Tetromino/TetrominoRotationEnum.hpp"
#include "../../h/Tetromino/TetrominoHelpers.hpp"

#include <iostream>

using namespace Tetromino;

namespace RotationSystem {
	bool SRS::Rotate(const std::vector<std::vector<TetrominoEnum>>& BoardState, TetrominoBase* tetromino, TetrominoRotationEnum rotateDir) const {
		int initialRotationStateIndex = tetromino->GetCurrentRotationStateIndex();
		int resultingRotationStateIndex = GetResultingRotationStateIndex(tetromino, rotateDir);
		
		std::vector<std::pair<int, int>> tests;
		auto& wallKickData = TetrominoByWallKickData.at(tetromino->GetTetrominoEnumEquivalent());
		std::cout << initialRotationStateIndex << ">>" << resultingRotationStateIndex << " tests: " << wallKickData.size() << '\n';
		
		if (wallKickData.size() != 0)
			tests = wallKickData[initialRotationStateIndex][resultingRotationStateIndex];

		if (tests.size() == 0) // add basic test
			tests.push_back({ 0, 0 });

		auto& resultingRotationState = tetromino->GetRotationStateAt(resultingRotationStateIndex);

		for (const auto& test : tests) {
			int newColOffset = tetromino->ColumnOffset + test.first;
			int newRowOffset = tetromino->RowOffset + (test.second * -1); // * -1 because wall kick translation in y is positive upwards and negative downwards, but std::vectors are the opposite
			bool canMove = CanMove(BoardState,
				resultingRotationState,
				newColOffset,
				newRowOffset); 
			if (canMove) {
				tetromino->ColumnOffset = newColOffset;
				tetromino->RowOffset = newRowOffset;
				tetromino->SetCurrentRotationStateIndex(resultingRotationStateIndex);
				return true;
			}
		}
		return false;
	}

	const std::vector<std::vector<std::vector<std::pair<int, int>>>> SRS::WallKickDataJLTSZ
	{
		{//[0]
			{//[0][0]

			},
			{//[0][1]
				{// 0>>1 Test1
					0, 0
				},
				{// 0>>1 Test2
					-1, 0
				},
				{// 0>>1 Test3
					-1, 1
				},
				{// 0>>1 Test4
					0, -2
				},
				{// 0>>1 Test5
					-1, -2
				}
			},
			{//[0][2]

			},
			{//[0][3]
				{// 0>>3 Test1
					0, 0
				},
				{// 0>>3 Test2
					1, 0
				},
				{// 0>>3 Test3
					1, 1
				},
				{// 0>>3 Test4
					0, -2
				},
				{// 0>>3 Test5
					1, -2
				}
			}
		},

		{//[1]
			{//[1][0]
				{// 1>>0 Test1
					0, 0
				},
				{// 1>>0 Test2
					1, 0
				},
				{// 1>>0 Test3
					1, -1
				},
				{// 1>>0 Test4
					0, 2
				},
				{// 1>>0 Test5
					1, 2
				}
			},
			{//[1][1]

			},
			{//[1][2]
				{// 1>>2 Test1
					0, 0
				},
				{// 1>>2 Test2
					1, 0
				},
				{// 1>>2 Test3
					1, -1
				},
				{// 1>>2 Test4
					0, 2
				},
				{// 1>>2 Test5
					1, 2
				}
			},
			{//[1][3]

			}
		},

		{//[2]
			{//[2][0]

			},
			{//[2][1]
				{// 2>>1 Test1
					0, 0
				},
				{// 2>>1 Test2
					-1, 0
				},
				{// 2>>1 Test3
					-1, 1
				},
				{// 2>>1 Test4
					0, -2
				},
				{// 2>>1 Test5
					-1, -2
				}
			},
			{//[2][2]

			},
			{//[2][3]
				{// 2>>3 Test1
					0, 0
				},
				{// 2>>3 Test2
					1, 0
				},
				{// 2>>3 Test3
					1, 1
				},
				{// 2>>3 Test4
					0, -2
				},
				{// 2>>3 Test5
					1, -2
				}
			}
		},

		{//[3]
			{//[3][0]
				{// 3>>0 Test1
					0, 0
				},
				{// 3>>0 Test2
					-1, 0
				},
				{// 3>>0 Test3
					-1, -1
				},
				{// 3>>0 Test4
					0, 2
				},
				{// 3>>0 Test5
					-1, 2
				}
			},
			{//[3][1]

			},
			{//[3][2]
				{// 3>>2 Test1
					0, 0
				},
				{// 3>>2 Test2
					-1, 0
				},
				{// 3>>2 Test3
					-1, -1
				},
				{// 3>>2 Test4
					0, 2
				},
				{// 3>>2 Test5
					-1, 2
				}
			},
			{//[3][3]

			}
		}
	};
	const std::vector<std::vector<std::vector<std::pair<int, int>>>> SRS::WallKickDataI
	{
		{//[0]
			{//[0][0]

			},
			{//[0][1]
				{// 0>>1 Test1
					0, 0
				},
				{// 0>>1 Test2
					-2, 0
				},
				{// 0>>1 Test3
					1, 0
				},
				{// 0>>1 Test4
					-2, -1
				},
				{// 0>>1 Test5
					1, 2
				}
			},
			{//[0][2]

			},
			{//[0][3]
				{// 0>>3 Test1
					0, 0
				},
				{// 0>>3 Test2
					-1, 0
				},
				{// 0>>3 Test3
					2, 0
				},
				{// 0>>3 Test4
					-1, 2
				},
				{// 0>>3 Test5
					2, -1
				}
			}
		},

		{//[1]
			{//[1][0]
				{// 1>>0 Test1
					0, 0
				},
				{// 1>>0 Test2
					2, 0
				},
				{// 1>>0 Test3
					-1, 0
				},
				{// 1>>0 Test4
					2, 1
				},
				{// 1>>0 Test5
					-1, -2
				}
			},
			{//[1][1]

			},
			{//[1][2]
				{// 1>>2 Test1
					0, 0
				},
				{// 1>>2 Test2
					-1, 0
				},
				{// 1>>2 Test3
					2, 0
				},
				{// 1>>2 Test4
					-1, 2
				},
				{// 1>>2 Test5
					2, -1
				}
			},
			{//[1][3]

			}
		},

		{//[2]
			{//[2][0]

			},
			{//[2][1]
				{// 2>>1 Test1
					0, 0
				},
				{// 2>>1 Test2
					1, 0
				},
				{// 2>>1 Test3
					-2, 0
				},
				{// 2>>1 Test4
					1, -2
				},
				{// 2>>1 Test5
					-2, 1
				}
			},
			{//[2][2]

			},
			{//[2][3]
				{// 2>>3 Test1
					0, 0
				},
				{// 2>>3 Test2
					2, 0
				},
				{// 2>>3 Test3
					-1, 0
				},
				{// 2>>3 Test4
					2, 1
				},
				{// 2>>3 Test5
					-1, -2
				}
			}
		},

		{//[3]
			{//[3][0]
				{// 3>>0 Test1
					0, 0
				},
				{// 3>>0 Test2
					1, 0
				},
				{// 3>>0 Test3
					-2, 0
				},
				{// 3>>0 Test4
					1, -2
				},
				{// 3>>0 Test5
					-2, 1
				}
			},
			{//[3][1]

			},
			{//[3][2]
				{// 3>>2 Test1
					0, 0
				},
				{// 3>>2 Test2
					-2, 0
				},
				{// 3>>2 Test3
					1, 0
				},
				{// 3>>2 Test4
					-2, -1
				},
				{// 3>>2 Test5
					1, 2
				}
			},
			{//[3][3]

			}
		}
	};

	const std::unordered_map<TetrominoEnum, std::vector<std::vector<std::vector<std::pair<int, int>>>>> SRS::TetrominoByWallKickData
	{
		{ J_, SRS::WallKickDataJLTSZ },
		{ L_, SRS::WallKickDataJLTSZ },
		{ T_, SRS::WallKickDataJLTSZ },
		{ S_, SRS::WallKickDataJLTSZ },
		{ Z_, SRS::WallKickDataJLTSZ },
		{ I_, SRS::WallKickDataI },
		{ O_, {} }
	};

	RotationSystemEnum SRS::GetRotationSystemEnumEquivalent() const {
		return RotationSystemEnumEquivalent;
	}
	const RotationSystemEnum SRS::RotationSystemEnumEquivalent(SRS_);

	const std::unordered_map<Tetromino::TetrominoEnum,
		std::vector<std::vector<std::vector<Tetromino::TetrominoEnum>>>>& SRS::GetTetrominoRotationStates() const {
		return TetrominoRotationStates;
	}
	const std::unordered_map<Tetromino::TetrominoEnum,
		std::vector<std::vector<std::vector<Tetromino::TetrominoEnum>>>> SRS::TetrominoRotationStates{
			{
				/* I */
				I_, 
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
			},
			{
				/* J */
				J_,
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
			},
			{
				/* L */
				L_,
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
			},
			{
				/* O */
				O_,
				{ {
					{
						{{_, O_, O_, _},
						 {_, O_, O_, _},
						 {_, _ , _ , _}}
					}
				} }
			},
			{
				/* S */
				S_,
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
			},
			{
				/* T */
				T_,
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
			},
			{
				/* Z */
				Z_,
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
			}
		};
}
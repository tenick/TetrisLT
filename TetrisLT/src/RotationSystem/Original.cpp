#include "../../h/RotationSystem/Original.hpp"

#include "../../h/Tetromino/TetrominoEnum.hpp"
#include "../../h/Tetromino/TetrominoBase.hpp"
#include "../../h/Tetromino/TetrominoRotationEnum.hpp"
#include "../../h/Tetromino/TetrominoHelpers.hpp"

using namespace Tetromino;

namespace RotationSystem {
	bool Original::Rotate(const std::vector<std::vector<TetrominoEnum>>& BoardState, TetrominoBase* tetromino, TetrominoRotationEnum rotateDir) const {
		int resultingRotationStateIndex = GetResultingRotationStateIndex(tetromino, rotateDir);
		auto& resultingRotationState = tetromino->GetRotationStateAt(resultingRotationStateIndex);

		bool canMove = CanMove(BoardState,
			resultingRotationState,
			tetromino->ColumnOffset,
			tetromino->RowOffset);
		if (canMove)
			tetromino->SetCurrentRotationStateIndex(resultingRotationStateIndex);
		return canMove;
	}

	RotationSystemEnum Original::GetRotationSystemEnumEquivalent() const {
		return RotationSystemEnumEquivalent;
	}
	const RotationSystemEnum Original::RotationSystemEnumEquivalent(Original_);

	const std::unordered_map<Tetromino::TetrominoEnum,
		std::vector<std::vector<std::vector<Tetromino::TetrominoEnum>>>>& Original::GetTetrominoRotationStates() const {
		return TetrominoRotationStates;
	}
	const std::unordered_map<Tetromino::TetrominoEnum,
		std::vector<std::vector<std::vector<Tetromino::TetrominoEnum>>>> Original::TetrominoRotationStates{
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
					}
				} }
			},
			{
				/* J */
				J_,
				{ {
					{
						{{_ , _ , _ },
						 {J_, J_, J_},
						 {_ , _ , J_}}
					},
					{
						{{_ , J_, _ },
						 {_ , J_, _ },
						 {J_, J_, _ }}
					},
					{
						{{J_, _ , _ },
						 {J_, J_, J_},
						 {_ , _ , _ }}
					},
					{
						{{_ , J_, J_},
						 {_ , J_, _ },
						 {_ , J_, _ }}
					}
				} }
			},
			{
				/* L */
				L_,
				{ {
					{
						{{_ , _ , _ },
						 {L_, L_, L_},
						 {L_ , _ , _ }}
					},
					{
						{{L_, L_, _ },
						 {_ , L_, _ },
						 {_ , L_, _ }}
					},
					{
						{{_ , _ , L_},
						 {L_, L_, L_},
						 {_ , _ , _ }}
					},
					{
						{{_ , L_, _ },
						 {_ , L_, _ },
						 {_ , L_, L_}}
					}
				} }
			},
			{
				/* O */
				O_,
				{ {
					{
						{{_, _ , _ , _},
						 {_, O_, O_, _},
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
						{{_ , _ , _ },
						 {_ , S_, S_},
						 {S_, S_, _ }}
					},
					{
						{{_ , S_, _ },
						 {_ , S_, S_},
						 {_ , _ , S_}}
					}
				} }
			},
			{
				/* T */
				T_,
				{ {
					{
						{{_ , _ , _ },
						 {T_, T_, T_},
						 {_ , T_, _ }}
					},
					{
						{{_ , T_, _ },
						 {T_, T_, _ },
						 {_ , T_, _ }}
					},
					{
						{{_ , T_, _ },
						 {T_, T_, T_},
						 {_ , _ , _ }}
					},
					{
						{{_ , T_, _ },
						 {_ , T_, T_},
						 {_ , T_, _ }}
					}
				} }
			},
			{
				/* Z */
				Z_,
				{ {
					{
						{{_ , _ , _ },
						 {Z_, Z_, _ },
						 {_ , Z_, Z_}}
					},
					{
						{{_ , _ , Z_},
						 {_ , Z_, Z_},
						 {_ , Z_, _ }}
					}
				} }
			}
	};
}
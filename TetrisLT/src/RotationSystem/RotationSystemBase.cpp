#include "../../h/RotationSystem/RotationSystemBase.hpp"

#include "../../h/Tetromino/TetrominoBase.hpp"

namespace RotationSystem {
	int RotationSystemBase::GetResultingRotationStateIndex(TetrominoBase* tetromino, TetrominoRotationEnum rotateDir) const {
		int resultingStateIndex = tetromino->GetCurrentRotationStateIndex();
		switch (rotateDir) {
		case R_CW:
			resultingStateIndex++;
			break;
		case R_CCW:
			resultingStateIndex--;
			break;
		case R_180:
			resultingStateIndex += 2;
			break;
		}

		return tetromino->AdjustRotationStateIndex(resultingStateIndex);
	}
}
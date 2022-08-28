#include "../../h/Tetromino/TetrominoHelpers.hpp"

#include "../../h/Tetromino/TetrominoEnum.hpp"
#include "../../h/RotationSystem/RotationSystemEnum.hpp"
#include "../../h/RotationSystem/SRS.hpp"
#include "../../h/RotationSystem/Original.hpp"

#include <vector>
#include <cstdint>

using namespace RotationSystem;

namespace Tetromino {

	/*  H E L P E R S  */
	void EnumToRGBA(TetrominoEnum tetrEnum, uint8_t& R, uint8_t& G, uint8_t& B, uint8_t& A);
	const std::vector<std::vector<std::vector<TetrominoEnum>>>& EnumToRotationStates(RotationSystem::RotationSystemEnum rsEnum, TetrominoEnum tetrEnum);
	bool CanMove(const std::vector<std::vector<TetrominoEnum>>& boardState, const std::vector<std::vector<TetrominoEnum>>& tetrominoState, int newColOffset, int newRowOffset);

	void EnumToRGBA(TetrominoEnum tetrEnum, uint8_t& R, uint8_t& G, uint8_t& B, uint8_t& A) {
		switch (tetrEnum) {
		case I_:
			R = 0x00; G = 0xFF; B = 0xFF; A = 0xFF; break; // cyan
		case J_:
			R = 0x00; G = 0x00; B = 0xFF; A = 0xFF; break; // blue
		case L_:
			R = 0xFF; G = 0xA5; B = 0x00; A = 0xFF; break; // orange
		case O_:
			R = 0xFF; G = 0xFF; B = 0x00; A = 0xFF; break; // yellow
		case S_:
			R = 0x00; G = 0xFF; B = 0x00; A = 0xFF; break; // green
		case T_:
			R = 0xA0; G = 0x20; B = 0xF0; A = 0xFF; break; // purple
		case Z_:
			R = 0xFF; G = 0x00; B = 0x00; A = 0xFF; break; // red
		}
	}

	const std::vector<std::vector<std::vector<TetrominoEnum>>>& EnumToRotationStates(RotationSystem::RotationSystemEnum rsEnum, TetrominoEnum tetrEnum) {
		using namespace RotationSystem;
		switch (rsEnum) {
		case SRS_:
			return SRS::TetrominoRotationStates.at(tetrEnum);
		case Original_:
			return Original::TetrominoRotationStates.at(tetrEnum);
		}
	}


	bool CanMove(const std::vector<std::vector<TetrominoEnum>>& boardState, const std::vector<std::vector<TetrominoEnum>>& tetrominoState, int newColOffset, int newRowOffset) {
		int boardHeight = boardState.size();
		int boardWidth = boardState[0].size();
		for (int c = 0; c < tetrominoState[0].size(); c++) {
			int boardC = newColOffset + c;
			for (int r = 0; r < tetrominoState.size(); r++) {
				int boardR = newRowOffset + r;

				if (boardC < 0 || boardC >= boardWidth || boardR >= boardHeight) { // means piece array is reaching outside of board
					// check if any piece is outside the board, can't move
					if (tetrominoState[r][c] != _)
						return false;
				}
				else { // means piece array is inside the board
					// check if any piece in array is touching any piece in board
					if (tetrominoState[r][c] != _ && boardState[boardR][boardC] != _)
						return false;
				}
			}
		}
		return true;
	}
}
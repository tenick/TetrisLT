#pragma once

#include "../Randomizer/RandomizerBase.hpp"
#include "../Randomizer/BagOf7.hpp"
#include "TetrominoBase.hpp"


namespace Tetromino {
	class TetrominoHandler {
	public:
		TetrominoHandler() = delete;
		TetrominoHandler(std::vector<std::vector<TetrominoEnum>>& boardState,
						 Randomizer::RandomizerBase* randomizer = new Randomizer::BagOf7());
		bool canMove(const std::vector<std::vector<TetrominoEnum>>& tetrominoState, int newColOffset, int newRowOffset);
		bool Move(TetrominoMoveEnum moveDir);
		bool Rotate(TetrominoRotationEnum rotateDir);
		void Next();
		TetrominoBase* GetHoldTetromino();
		TetrominoBase* GetCurrentTetromino();
		void HoldTetromino();
		std::array<TetrominoBase*, 5> PeekNext5Tetrominos();
		~TetrominoHandler();
	private:
		std::vector<std::vector<TetrominoEnum>>& BoardState;
		const int BoardHeight;
		const int BoardWidth;
		TetrominoBase* currentTetromino = nullptr;
		TetrominoBase* holdTetromino = nullptr;
		Randomizer::RandomizerBase* randomizer;
	};
}

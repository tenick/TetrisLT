#ifndef TETROMINO_HELPERS_H
#define TETROMINO_HELPERS_H

#include "TetrominoEnum.hpp"
#include <cstdint>
#include <vector>
#include "../RotationSystem/RotationSystemEnum.hpp"
#include "../RotationSystem/SRS.hpp"

#include <SDL.h>

namespace Tetromino {
	void EnumToRGBA(TetrominoEnum tetrEnum, uint8_t& R, uint8_t& G, uint8_t& B, uint8_t& A);
	const std::vector<std::vector<std::vector<TetrominoEnum>>>& EnumToRotationStates(RotationSystem::RotationSystemEnum rsEnum, TetrominoEnum tetrEnum);
	bool CanMove(const std::vector<std::vector<TetrominoEnum>>& boardState, const std::vector<std::vector<TetrominoEnum>>& tetrominoState, int newColOffset, int newRowOffset);
	void RenderTexture(SDL_Renderer* renderCtx, SDL_Texture* texture, SDL_FRect* renderRect, TetrominoEnum tetromino);
}

#endif
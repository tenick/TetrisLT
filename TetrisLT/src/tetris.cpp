#include "../h/tetris.hpp"
#include "../h/Tetromino/I.hpp"
#include "../h/Randomizer/RandomizerBase.hpp"
#include "../h/Randomizer/BagOf7.hpp"
#include <iostream>

Tetris::Tetris(SDL_Window*& windowContext, SDL_Renderer*& renderContext, int rows, int columns) :
	windowContext(windowContext),
	renderContext(renderContext),
	ROWS(rows),
	COLUMNS(columns),
	BoardState(std::vector<std::vector<TetrominoEnum>>(rows, std::vector<TetrominoEnum>(columns, _))),
	tetrominoHandler(TetrominoHandler(BoardState))
{
}

void Tetris::OnWindowEvent() {
	this->UpdateViewportByWindowSize();
}

void Tetris::UpdateViewportByWindowSize() {
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	SDL_GetWindowSize(this->windowContext, &SCREEN_WIDTH, &SCREEN_HEIGHT);
	SDL_SetWindowMinimumSize(this->windowContext, SCREEN_HEIGHT / 3 + SCREEN_HEIGHT / 2, 100);

	this->boardViewport.w = SCREEN_HEIGHT / 2;
	this->boardViewport.h = SCREEN_HEIGHT;
	this->boardViewport.x = SCREEN_WIDTH / 2 - this->boardViewport.w / 2;
	this->boardViewport.y = 0;

	this->swapViewport.w = SCREEN_HEIGHT / 6;
	this->swapViewport.h = SCREEN_HEIGHT / 6;
	this->swapViewport.x = SCREEN_WIDTH / 2 - this->boardViewport.w / 2 - this->swapViewport.w;
	this->swapViewport.y = 0;

	this->next5Viewport.w = SCREEN_HEIGHT / 6;
	this->next5Viewport.h = SCREEN_HEIGHT / 6 * 5;
	this->next5Viewport.x = SCREEN_WIDTH / 2 + this->boardViewport.w / 2;
	this->next5Viewport.y = 0;
}

void Tetris::Update() {
	// update tetris states (time to get next piece? time to randomize? etc...)
	//this->Randomizer.Add(Tetromino::I());
	// TODO: lock delay w/ limit after resetting of lock delay due to move/rotation of piece
	// TODO: adding falling of tetromino via gameplay fall speed

	// handle keyboard
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	// harddrop input
	if (currentKeyStates[this->HardDrop])
	{
		if (!onHarddrop) {
			while (this->tetrominoHandler.Move(M_D))
				continue;
			
			auto currentTetromino = this->tetrominoHandler.GetCurrentTetromino();
			auto currentTetrominoState = currentTetromino->GetCurrentState();
			// add current tetromino to the board state
			for (int r = 0; r < currentTetromino->GetHeight(); r++) {
				for (int c = 0; c < currentTetromino->GetWidth(); c++) {
					int boardR = r + currentTetromino->GetRowOffset();
					int boardC = c + currentTetromino->GetColumnOffset();
					if (currentTetrominoState[r][c] != _)
						this->BoardState[boardR][boardC] = currentTetrominoState[r][c];
				}
			}
			this->tetrominoHandler.Next();
			onHarddrop = true;
		}
	}
	else
		onHarddrop = false;

	// softdrop input
	if (currentKeyStates[this->SoftDrop])
	{
		if (!this->SDSActivated) {
			this->tetrominoHandler.Move(M_D);
			this->currentSDS = SDL_GetTicks64();
			this->SDSActivated = true;
		}
		else if (this->SDSActivated && SDL_GetTicks64() - this->currentSDS >= this->SDS) {
			this->tetrominoHandler.Move(M_D);
			this->currentSDS = SDL_GetTicks64();
		}
	}
	else {
		this->SDSActivated = false;
		this->currentSDS = 0;
	}

	// rotation CW, CCW, and 180
	if (currentKeyStates[this->RotateCW]) {
		if (!this->onCWRotate) {
			this->tetrominoHandler.Rotate(TetrominoRotationEnum::R_CW);
			this->onCWRotate = true;
		}
	}
	else
		this->onCWRotate = false;
	if (currentKeyStates[this->RotateCCW]) {
		if (!this->onCCWRotate) {
			this->tetrominoHandler.Rotate(TetrominoRotationEnum::R_CCW);
			this->onCCWRotate = true;
		}
	}
	else
		this->onCCWRotate = false;
	if (currentKeyStates[this->Rotate180]) {
		if (!this->on180Rotate) {
			this->tetrominoHandler.Rotate(TetrominoRotationEnum::R_180);
			this->on180Rotate = true;
		}
	}
	else
		this->on180Rotate = false;

	
	// move left/right
	if (currentKeyStates[this->MoveLeft] || currentKeyStates[this->MoveRight])
	{
		if (!this->ARRActivated) {
			if (!this->onDAS) {
				if (currentKeyStates[this->MoveLeft])
					this->tetrominoHandler.Move(M_L);
				else
					this->tetrominoHandler.Move(M_R);
				this->onDAS = true;
				this->currentDAS = SDL_GetTicks64();
			}
			else if (this->onDAS && SDL_GetTicks64() - this->currentDAS >= this->DAS) {
				this->ARRActivated = true;
				this->currentARR = SDL_GetTicks();
			}
		}
		else if (this->ARRActivated && SDL_GetTicks64() - this->currentARR >= this->ARR) {
			if (currentKeyStates[this->MoveLeft])
				this->tetrominoHandler.Move(M_L);
			else
				this->tetrominoHandler.Move(M_R);
			this->currentARR = SDL_GetTicks();
		}
	}
	else {
		this->ARRActivated = false;
		this->onDAS = false;
		this->currentDAS = 0;
		this->currentARR = 0;
	}

}

void Tetris::Render() {

	// draw current board state in board viewport
	SDL_RenderSetViewport(this->renderContext, &this->boardViewport);
	SDL_FRect cellRect{};
	cellRect.w = (float)this->boardViewport.w / this->COLUMNS;
	cellRect.h = (float)this->boardViewport.h / this->ROWS;
	SDL_SetRenderDrawColor(this->renderContext, 0xBB, 0xBB, 0xBB, 0xFF);
	for (int r = 0; r < this->ROWS; r++) {
		for (int c = 0; c < this->COLUMNS; c++) {
			TetrominoEnum currCell = this->BoardState[r][c];
			if (currCell == _)
				SDL_SetRenderDrawColor(this->renderContext, 0xBB, 0xBB, 0xBB, 0xFF);
			else // TODO: add EnumToColor helper function
				SDL_SetRenderDrawColor(this->renderContext, 0x33, 0x33, 0x33, 0xFF);

			cellRect.x = c * cellRect.w;
			cellRect.y = r * cellRect.h;
			SDL_RenderFillRectF(this->renderContext, &cellRect);
		}
	}

	// draw board lines
	SDL_SetRenderDrawColor(this->renderContext, 0xFF, 0xFF, 0xFF, 0xFF);
	float cellHeight = (float)this->boardViewport.h / this->ROWS;
	float cellWidth = (float)this->boardViewport.w / this->COLUMNS;
	for (int i = 1; i < this->ROWS; i++) {
		float currY = i * cellHeight;
		SDL_RenderDrawLineF(this->renderContext, 0, currY, this->boardViewport.w, currY);
	}
	for (int i = 1; i < this->COLUMNS; i++) {
		float currX = i * cellWidth;
		SDL_RenderDrawLineF(this->renderContext, currX, 0, currX, this->boardViewport.h);
	}

	// draw current tetromino
	TetrominoBase* currentTetromino = this->tetrominoHandler.GetCurrentTetromino();
	int currentColumnOffset = currentTetromino->GetColumnOffset();
	int currentRowOffset = currentTetromino->GetRowOffset();
	auto currentTetrominoState = currentTetromino->GetCurrentState();
	// TODO: add EnumToColor helper function
	SDL_SetRenderDrawColor(this->renderContext, 0x33, 0x33, 0x33, 0xFF);
	for (int r = 0; r < currentTetrominoState.size(); r++) {
		for (int c = 0; c < currentTetrominoState[0].size(); c++) {
			TetrominoEnum currCell = currentTetrominoState[r][c];

			if (currCell != _) {
				cellRect.x = (currentColumnOffset + c) * cellRect.w;
				cellRect.y = (currentRowOffset + r) * cellRect.h;
				SDL_RenderFillRectF(this->renderContext, &cellRect);
			}
		}
	}

	// draw current tetromino shadow
	int resultingRowOffset = currentRowOffset;
	while (tetrominoHandler.canMove(currentTetrominoState, currentColumnOffset, resultingRowOffset + 1)) {
		resultingRowOffset++;
	}
	for (int r = 0; r < currentTetrominoState.size(); r++) {
		for (int c = 0; c < currentTetrominoState[0].size(); c++) {
			TetrominoEnum currCell = currentTetrominoState[r][c];

			if (currCell != _) {
				cellRect.x = (currentColumnOffset + c) * cellRect.w;
				cellRect.y = (resultingRowOffset + r) * cellRect.h;
				SDL_RenderFillRectF(this->renderContext, &cellRect);
			}
		}
	}


	// draw swap viewport
	SDL_RenderSetViewport(this->renderContext, &this->swapViewport);
	SDL_FRect boardRect{};
	boardRect.w = this->swapViewport.w;
	boardRect.h = this->swapViewport.h;
	SDL_SetRenderDrawColor(this->renderContext, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRectF(this->renderContext, &boardRect);

	// draw next 5 viewport
	SDL_RenderSetViewport(this->renderContext, &this->next5Viewport);
	boardRect.w = this->next5Viewport.w;
	boardRect.h = this->next5Viewport.h;
	SDL_SetRenderDrawColor(this->renderContext, 0x00, 0xFF, 0x00, 0xFF);
	SDL_RenderFillRectF(this->renderContext, &boardRect);

	
}
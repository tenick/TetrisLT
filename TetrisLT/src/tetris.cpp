#include "../h/tetris.hpp"

#include "../h/Tetromino/TetrominoHelpers.hpp"

Tetris::Tetris(SDL_Window*& windowContext, SDL_Renderer*& renderContext, int rows, int columns, int vanishZoneHeight) :
	windowContext(windowContext),
	renderContext(renderContext),
	ROWS(rows + vanishZoneHeight),
	COLUMNS(columns),
	VANISHZONEHEIGHT(vanishZoneHeight),
	BoardState(std::vector<std::vector<TetrominoEnum>>(rows + vanishZoneHeight, std::vector<TetrominoEnum>(columns, _))),
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
	this->swapViewport.y = SCREEN_HEIGHT / 6;

	this->next5Viewport.w = SCREEN_HEIGHT / 6;
	this->next5Viewport.h = SCREEN_HEIGHT / 6 * 5;
	this->next5Viewport.x = SCREEN_WIDTH / 2 + this->boardViewport.w / 2;
	this->next5Viewport.y = SCREEN_HEIGHT / 6;
}

void Tetris::Update() {
	this->tetrominoHandler.Update();
}

void Tetris::Render() {

	// drawing current board state
	SDL_RenderSetViewport(this->renderContext, &this->boardViewport);
	SDL_FRect cellRect{};

	cellRect.w = (float)this->boardViewport.w / this->COLUMNS;
	cellRect.h = (float)this->boardViewport.h / this->ROWS;
	
		
	for (int r = 0; r < this->ROWS; r++) {
		for (int c = 0; c < this->COLUMNS; c++) {
			TetrominoEnum currCell = this->BoardState[r][c];
			if (currCell == _)
				SDL_SetRenderDrawColor(this->renderContext, 0xBB, 0xBB, 0xBB, 0xFF);
			else {
				uint8_t r, g, b, a;
				Tetromino::EnumToRGBA(currCell, r, g, b, a);
				SDL_SetRenderDrawColor(this->renderContext, r, g, b, a);
			}

			cellRect.x = c * cellRect.w;
			cellRect.y = r * cellRect.h;
			SDL_RenderFillRectF(this->renderContext, &cellRect);
		}
	}
		// draw over board to represent vanish zone (black bg)
	SDL_SetRenderDrawColor(this->renderContext, 0x00, 0x00, 0x00, 0xFF);
	for (int r = 0; r < this->VANISHZONEHEIGHT; r++) {
		for (int c = 0; c < this->COLUMNS; c++) {
			TetrominoEnum currCell = this->BoardState[r][c];
			if (currCell == _){
				cellRect.x = c * cellRect.w;
				cellRect.y = r * cellRect.h;
				SDL_RenderFillRectF(this->renderContext, &cellRect);
			}
		}
	}

	//// draw board lines
	//SDL_SetRenderDrawColor(this->renderContext, 0xFF, 0xFF, 0xFF, 0xFF);
	//float cellHeight = (float)this->boardViewport.h / this->ROWS;
	//float cellWidth = (float)this->boardViewport.w / this->COLUMNS;
	//for (int i = 1; i < this->ROWS; i++) {
	//	float currY = i * cellHeight;
	//	SDL_RenderDrawLineF(this->renderContext, 0, currY, this->boardViewport.w, currY);
	//}
	//for (int i = 1; i < this->COLUMNS; i++) {
	//	float currX = i * cellWidth;
	//	SDL_RenderDrawLineF(this->renderContext, currX, 0, currX, this->boardViewport.h);
	//}

	// draw current tetromino
	SDL_SetRenderDrawColor(this->renderContext, (uint8_t)0xFF, (uint8_t)0x00, (uint8_t)0x00, (uint8_t)0xFF);
	TetrominoBase* currentTetromino = this->tetrominoHandler.GetCurrentTetromino();
	int currentColumnOffset = currentTetromino->ColumnOffset;
	int currentRowOffset = currentTetromino->RowOffset;
	auto& currentTetrominoState = currentTetromino->GetCurrentRotationState();


	uint8_t r, g, b, a;
	Tetromino::EnumToRGBA(currentTetromino->GetTetrominoEnumEquivalent(), r, g, b, a);
	SDL_SetRenderDrawColor(this->renderContext, r, g, b, a);
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
	while (CanMove(this->BoardState, currentTetrominoState, currentColumnOffset, resultingRowOffset + 1)) {
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
	TetrominoEnum holdTetromino = this->tetrominoHandler.GetHoldTetromino();
	SDL_FRect viewportRect{};
	if (holdTetromino != _) {
		SDL_RenderSetViewport(this->renderContext, &this->swapViewport);

		// clear swap viewport 1st by rendering black bg
		viewportRect.w = this->swapViewport.w;
		viewportRect.h = this->swapViewport.h;
		SDL_SetRenderDrawColor(this->renderContext, 0, 0, 0, 0);
		SDL_RenderFillRectF(this->renderContext, &viewportRect);


		Tetromino::EnumToRGBA(holdTetromino, r, g, b, a);
		SDL_SetRenderDrawColor(this->renderContext, r, g, b, a);

		auto& holdTetrominoState = EnumToRotationStates(this->tetrominoHandler.GetRotationSystemEnumEquivalent(), holdTetromino)[0];

		cellRect.w = this->swapViewport.w / holdTetrominoState[0].size();
		cellRect.h = this->swapViewport.h / holdTetrominoState.size();

		for (int r = 0; r < holdTetrominoState.size(); r++) {
			for (int c = 0; c < holdTetrominoState[0].size(); c++) {
				TetrominoEnum currCell = holdTetrominoState[r][c];

				if (currCell != _) {
					cellRect.x = c * cellRect.w;
					cellRect.y = r * cellRect.h;
					SDL_RenderFillRectF(this->renderContext, &cellRect);
				}
			}
		}
	}
	

	// draw next 5 viewport
	SDL_RenderSetViewport(this->renderContext, &this->next5Viewport);

	// clear next 5 viewport 1st by rendering black bg
	viewportRect.w = this->next5Viewport.w;
	viewportRect.h = this->next5Viewport.h;
	SDL_SetRenderDrawColor(this->renderContext, 0, 0, 0, 0);
	SDL_RenderFillRectF(this->renderContext, &viewportRect);

	auto next5Tetrominos = this->tetrominoHandler.PeekNext5Tetrominos();

	cellRect.w = this->next5Viewport.w;
	cellRect.h = this->next5Viewport.h / 5;
	for (int i = 0; i < next5Tetrominos.size(); i++) {

		Tetromino::EnumToRGBA(next5Tetrominos[i], r, g, b, a);
		SDL_SetRenderDrawColor(this->renderContext, r, g, b, a);

		auto& tetrominoState = EnumToRotationStates(this->tetrominoHandler.GetRotationSystemEnumEquivalent(), next5Tetrominos[i])[0];

		cellRect.w = this->next5Viewport.w / tetrominoState[0].size();
		cellRect.h = this->next5Viewport.h / tetrominoState.size() / 5;

		for (int r = 0; r < tetrominoState.size(); r++) {
			for (int c = 0; c < tetrominoState[0].size(); c++) {
				TetrominoEnum currCell = tetrominoState[r][c];

				if (currCell != _) {
					cellRect.x = c * cellRect.w;
					cellRect.y = r * cellRect.h + i * this->next5Viewport.h / 5;
					SDL_RenderFillRectF(this->renderContext, &cellRect);
				}
			}
		}
	}

	
}
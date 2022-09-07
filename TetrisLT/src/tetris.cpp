#include "../h/tetris.hpp"

#include "../h/Tetromino/TetrominoHelpers.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <chrono>

Tetris::Tetris(SDL_Window*& windowContext, int rows, int columns, int vanishZoneHeight) :
	windowContext(windowContext),
	renderContext(SDL_GetRenderer(windowContext)),
	ROWS(rows + vanishZoneHeight),
	COLUMNS(columns),
	VANISHZONEHEIGHT(vanishZoneHeight),
	BoardState(std::vector<std::vector<TetrominoEnum>>(this->ROWS, std::vector<TetrominoEnum>(this->COLUMNS, _))),
	tetrominoHandler(new TetrominoHandler(BoardState))
{
	MainFont = TTF_OpenFont("fonts/Silkscreen-Regular.ttf", 28);
	if (MainFont == NULL) {
		std::cout << "error: " << TTF_GetError() << '\n';
	}
}
const TetrisStats& Tetris::GetStats() const {
	return this->tetrominoHandler->CurrentStats();
}

void Tetris::OnWindowEvent() {
	this->UpdateViewportByWindowSize();
}

void Tetris::SetViewport(SDL_Rect newViewport) {
	this->playfieldViewport = newViewport;
}

const SDL_Rect& Tetris::Viewport() {
	return this->playfieldViewport;
}

void Tetris::UpdateViewportByWindowSize() {
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	SDL_GetWindowSize(this->windowContext, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	/* --------------------------------------------------------------------------------
	   (n:n = Width:Height)
	   playfield viewport must strictly be 1:1 aspect ratio 
	   playfield will have 3 parts: hold piece area, board area, and next 5 pieces area
	   hold piece area = 1:4
	   board area = 1:2
	   next 5 pieces area = 1:4
	   -------------------------------------------------------------------------------- */
	this->playfieldViewport.w = fmin(SCREEN_WIDTH, SCREEN_HEIGHT);
	this->playfieldViewport.h = this->playfieldViewport.w;

	this->playfieldViewport.x = 0;
	this->playfieldViewport.y = 0;
	if (SCREEN_HEIGHT > SCREEN_WIDTH) 
		this->playfieldViewport.y = (fmax(SCREEN_WIDTH, SCREEN_HEIGHT) - this->playfieldViewport.h) / 2;
	else
		this->playfieldViewport.x = (fmax(SCREEN_WIDTH, SCREEN_HEIGHT) - this->playfieldViewport.w) / 2;
}

bool Tetris::IsFinished() {
	return this->isFinished;
}


void Tetris::OnFinish() {
	this->isFinished = true;

	// replace current pieces in board with garbage (to indicate it's finished)
	for (int r = 0; r < this->BoardState.size(); r++) {
		for (int c = 0; c < this->BoardState[r].size(); c++) {
			TetrominoEnum tetrEnum = this->BoardState[r][c];
			if (tetrEnum != _)
				this->BoardState[r][c] = G_;
		}
	}
}

void Tetris::Reset() {
	this->tetrominoHandler->Reset();
	
	// clear renderer
	SDL_SetRenderDrawColor(this->renderContext, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(this->renderContext);

	// clear board
	for (int r = 0; r < this->ROWS; r++) {
		for (int c = 0; c < this->COLUMNS; c++) {
			this->BoardState[r][c] = _;
		}
	}

	this->isFinished = false;
}

void Tetris::Update() {
	if (!this->isFinished)
		this->tetrominoHandler->Update();
}

void Tetris::Render() {
	// draw playfield viewport bg
	SDL_RenderSetViewport(this->renderContext, &this->playfieldViewport);
	//SDL_SetRenderDrawColor(this->renderContext, 0x22, 0x22, 0x22, 0xff);
	//SDL_RenderFillRect(this->renderContext, &this->playfieldViewport);


	// drawing current board state
	SDL_FRect boardBG{};
	boardBG.w = (float)this->playfieldViewport.w / 2;
	boardBG.h = this->playfieldViewport.h;
	boardBG.x = boardBG.w / 2;
	boardBG.y = 0;
	SDL_SetRenderDrawColor(this->renderContext, 0x00, 0x00, 0x00, 0xff);
	SDL_RenderFillRectF(this->renderContext, &boardBG);


	SDL_FRect boardXYPadding{};
	SDL_FRect cellRect{};

	cellRect.w = boardBG.w / this->COLUMNS;
	cellRect.h = cellRect.w;

	boardXYPadding.y = fmax(0, (boardBG.h - cellRect.h * this->ROWS) / 2);


	// check if drawing board will overlap screen, adjust cell rect width and height
	if (cellRect.h * this->ROWS > boardBG.h) {
		cellRect.h = boardBG.h / this->ROWS;
		cellRect.w = cellRect.h;

		boardXYPadding.x = (boardBG.w - cellRect.w * this->COLUMNS) / 2;
	}

		
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

			cellRect.x = boardBG.x + boardXYPadding.x + c * cellRect.w;
			cellRect.y = boardBG.y + boardXYPadding.y + r * cellRect.h;
			SDL_RenderFillRectF(this->renderContext, &cellRect);
		}
	}
		// draw over board to represent vanish zone (black bg)
	SDL_SetRenderDrawColor(this->renderContext, 0x00, 0x00, 0x00, 0xFF);
	for (int r = 0; r < this->VANISHZONEHEIGHT; r++) {
		for (int c = 0; c < this->COLUMNS; c++) {
			TetrominoEnum currCell = this->BoardState[r][c];
			if (currCell == _){
				cellRect.x = boardBG.x + boardXYPadding.x + c * cellRect.w;
				cellRect.y = boardBG.y + boardXYPadding.y + r * cellRect.h;
				SDL_RenderFillRectF(this->renderContext, &cellRect);
			}
		}
	}
	
	// draw board lines
	/*SDL_SetRenderDrawColor(this->renderContext, 0x88, 0x88, 0x88, 0xFF);
	float cellHeight = (float)this->boardViewport.h / this->ROWS;
	float cellWidth = (float)this->boardViewport.w / this->COLUMNS;
	for (int i = 1; i < this->ROWS; i++) {
		float currY = i * cellHeight;
		SDL_RenderDrawLineF(this->renderContext, 0, currY, this->boardViewport.w, currY);
	}
	for (int i = 1; i < this->COLUMNS; i++) {
		float currX = i * cellWidth;
		SDL_RenderDrawLineF(this->renderContext, currX, 0, currX, this->boardViewport.h);
	}*/

	// draw current tetromino
	TetrominoBase*& currentTetromino = this->tetrominoHandler->GetCurrentTetromino();
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
				cellRect.x = boardBG.x + boardXYPadding.x + (currentColumnOffset + c) * cellRect.w;
				cellRect.y = boardBG.y + boardXYPadding.y + (currentRowOffset + r) * cellRect.h;
				SDL_RenderFillRectF(this->renderContext, &cellRect);
			}
		}
	}


	// draw current tetromino ghost piece
	if (this->isGhostPieceEnabled) {
		SDL_SetRenderDrawBlendMode(this->renderContext, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(this->renderContext, r * .7, g * .7, b * .7, 0xBB);
		int resultingRowOffset = currentRowOffset;
		while (CanMove(this->BoardState, currentTetrominoState, currentColumnOffset, resultingRowOffset + 1)) {
			resultingRowOffset++;
		}
		for (int r = 0; r < currentTetrominoState.size(); r++) {
			for (int c = 0; c < currentTetrominoState[0].size(); c++) {
				TetrominoEnum currCell = currentTetrominoState[r][c];

				if (currCell != _) {
					cellRect.x = boardBG.x + boardXYPadding.x + (currentColumnOffset + c) * cellRect.w;
					cellRect.y = boardBG.y + boardXYPadding.y + (resultingRowOffset + r) * cellRect.h;
					SDL_RenderFillRectF(this->renderContext, &cellRect);
				}
			}
		}
		SDL_SetRenderDrawBlendMode(this->renderContext, SDL_BLENDMODE_NONE);
	}


	// draw hold piece area
	SDL_FRect holdPieceBG{};
	holdPieceBG.w = (float)this->playfieldViewport.w / 4;
	holdPieceBG.h = this->playfieldViewport.h - cellRect.h * 4;
	holdPieceBG.x = 0;
	holdPieceBG.y = cellRect.h * 4;
	SDL_SetRenderDrawColor(this->renderContext, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderFillRectF(this->renderContext, &holdPieceBG);

	// 1 piece area, for hold piece and next 5 pieces, should be 1/6 of the height ^2
	SDL_FRect holdAndNext5PiecesArea{ 0, 0, holdPieceBG.h / 6, holdPieceBG.h / 6 };
	cellRect.w = holdAndNext5PiecesArea.w / 4;
	cellRect.h = holdAndNext5PiecesArea.h / 4;

	TetrominoEnum holdTetromino = this->tetrominoHandler->GetHoldTetromino();
	SDL_FRect viewportRect{};
	if (holdTetromino != _) {

		Tetromino::EnumToRGBA(holdTetromino, r, g, b, a);
		SDL_SetRenderDrawColor(this->renderContext, r, g, b, a);

		auto& holdTetrominoState = EnumToRotationStates(this->tetrominoHandler->GetRotationSystemEnumEquivalent(), holdTetromino)[0];

		for (int r = 0; r < holdTetrominoState.size(); r++) {
			for (int c = 0; c < holdTetrominoState[0].size(); c++) {
				TetrominoEnum currCell = holdTetrominoState[r][c];

				if (currCell != _) {
					cellRect.x = c * cellRect.w + ((holdPieceBG.w - holdTetrominoState[0].size() * cellRect.w) / 2);
					cellRect.y = r * cellRect.h + holdPieceBG.y;
					SDL_RenderFillRectF(this->renderContext, &cellRect);
				}
			}
		}
	}
	

	// draw next 5 viewport
	// draw next 5 pieces area
	SDL_FRect next5PiecesBG{};
	next5PiecesBG.w = holdPieceBG.w;
	next5PiecesBG.h = holdPieceBG.h;
	next5PiecesBG.x = holdPieceBG.w + boardBG.w;
	next5PiecesBG.y = holdPieceBG.y;
	SDL_SetRenderDrawColor(this->renderContext, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderFillRectF(this->renderContext, &next5PiecesBG);

	const std::array<TetrominoEnum, 5> next5Tetrominos = this->tetrominoHandler->PeekNext5Tetrominos();

	for (int i = 0; i < next5Tetrominos.size(); i++) {

		Tetromino::EnumToRGBA(next5Tetrominos[i], r, g, b, a);
		SDL_SetRenderDrawColor(this->renderContext, r, g, b, a);

		auto& tetrominoState = EnumToRotationStates(this->tetrominoHandler->GetRotationSystemEnumEquivalent(), next5Tetrominos[i])[0];

		for (int r = 0; r < tetrominoState.size(); r++) {
			for (int c = 0; c < tetrominoState[0].size(); c++) {
				TetrominoEnum currCell = tetrominoState[r][c];

				if (currCell != _) {
					cellRect.x = next5PiecesBG.x + c * cellRect.w;
					cellRect.y = next5PiecesBG.y + r * cellRect.h + i * holdAndNext5PiecesArea.h;
					SDL_RenderFillRectF(this->renderContext, &cellRect);
				}
			}
		}
	}
}

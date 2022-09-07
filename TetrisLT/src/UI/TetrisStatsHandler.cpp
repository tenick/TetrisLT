#include "../../h/UI/TetrisStatsHandler.hpp"
#include <iostream>
#include "../../h/helpers.hpp"

namespace UI {
	TetrisStatsHandler::TetrisStatsHandler(SDL_Renderer*& renderCtx, const Timer& timer, const SDL_Rect& tetrisViewPort, const TetrisStats& tetrisStats)
		: renderCtx(renderCtx), timer(timer), tetrisViewPort(tetrisViewPort), tetrisStats(tetrisStats)
	{
		this->MainFont = TTF_OpenFont("fonts/Silkscreen-Regular.ttf", 28);
		if (this->MainFont == NULL) {
			std::cout << "error: " << TTF_GetError() << '\n';
		}
	}

	const TetrisStats& TetrisStatsHandler::GetLastStats() const {
		return this->finalGameStats;
	}

	void TetrisStatsHandler::Update() {

		// convert ms to string MM:SS format
		int currTimeInMS = this->timer.CurrentTick();
		this->strCurrTime = Helpers::MStoMM_SSformat(this->timer.CurrentTick());


		// calculate pps
		float PPSf = std::roundf((float)this->tetrisStats.PiecesLocked / currTimeInMS * 1000 * 100) / 100.0f;

		std::stringstream stream;
		stream << std::fixed << std::setprecision(2) << PPSf;

		this->strCurrPPS = "PPS: " + stream.str();

		// update stats
		this->finalGameStats.gameDurationInMS = currTimeInMS;
		this->finalGameStats.LinesCleared = this->tetrisStats.LinesCleared;
		this->finalGameStats.PiecesLocked = this->tetrisStats.PiecesLocked;
		this->finalGameStats.PPS = PPSf;
	}

	void TetrisStatsHandler::Render() {
		// TEXT SECTION
		// render the texts
		SDL_RenderSetViewport(this->renderCtx, &this->tetrisViewPort);

		float containerWidth = this->tetrisViewPort.w / 4;
		float containerHeight = this->tetrisViewPort.h;


		// username text
		// calculate ratio of text to container width to make sure text fits its container (holdPieceArea)
		int tw, th;
		TTF_SizeText(this->MainFont, "Kenneth", &tw, &th);
		float twRatio = containerWidth / tw;
		float thRatio = (float)th / tw;
		float newTw = twRatio * tw;
		float newTh = thRatio * twRatio * tw;
		float usernameHeight = newTh;
		SDL_FRect textRect{ 0, containerHeight / 3, newTw, newTh };

		SDL_Surface* textSurface = TTF_RenderText_Solid(this->MainFont, "Kenneth", { 255,255,255,255 });

		//Create texture from surface pixels
		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(this->renderCtx, textSurface);

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
		SDL_RenderCopyF(this->renderCtx, textTexture, NULL, &textRect);

		// delete the text texture
		SDL_DestroyTexture(textTexture);


		// time text 
		// time width must be 1/8th of the viewport width, figure out the height
		TTF_SizeText(this->MainFont, this->strCurrTime.c_str(), &tw, &th);
		twRatio = (float)this->tetrisViewPort.w / 8 / tw;
		thRatio = (float)th / tw;
		newTw = twRatio * tw;
		newTh = thRatio * twRatio * tw;
		textRect = { (float)this->tetrisViewPort.w / 2 - newTw / 2, 0, newTw, newTh };

		textSurface = TTF_RenderText_Solid(this->MainFont, this->strCurrTime.c_str(), { 255,255,255,255 });

		//Create texture from surface pixels
		textTexture = SDL_CreateTextureFromSurface(this->renderCtx, textSurface);

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
		SDL_RenderCopyF(this->renderCtx, textTexture, NULL, &textRect);

		// delete the text texture
		SDL_DestroyTexture(textTexture);


		// PPS text
		TTF_SizeText(this->MainFont, this->strCurrPPS.c_str(), &tw, &th);
		twRatio = containerWidth / tw;
		thRatio = (float)th / tw;
		newTw = twRatio * tw;
		newTh = thRatio * twRatio * tw;
		float PPSheight = newTh;
		textRect = { 0, containerHeight / 3 + usernameHeight, newTw, newTh };

		textSurface = TTF_RenderText_Solid(this->MainFont, this->strCurrPPS.c_str(), { 255,255,255,255 });

		//Create texture from surface pixels
		textTexture = SDL_CreateTextureFromSurface(this->renderCtx, textSurface);

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
		SDL_RenderCopyF(this->renderCtx, textTexture, NULL, &textRect);

		// delete the text texture
		SDL_DestroyTexture(textTexture);


		// Lines text
		std::string lines = "Lines: " + std::to_string(this->tetrisStats.LinesCleared);

		TTF_SizeText(this->MainFont, lines.c_str(), &tw, &th);
		twRatio = containerWidth / tw;
		thRatio = (float)th / tw;
		newTw = twRatio * tw;
		newTh = thRatio * twRatio * tw;
		textRect = { 0, containerHeight / 3 + usernameHeight + PPSheight, newTw, newTh };

		textSurface = TTF_RenderText_Solid(this->MainFont, lines.c_str(), { 255,255,255,255 });

		//Create texture from surface pixels
		textTexture = SDL_CreateTextureFromSurface(this->renderCtx, textSurface);

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
		SDL_RenderCopyF(this->renderCtx, textTexture, NULL, &textRect);

		// delete the text texture
		SDL_DestroyTexture(textTexture);
	}
}
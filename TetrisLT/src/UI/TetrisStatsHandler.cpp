#include "../../h/UI/TetrisStatsHandler.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <chrono>

namespace UI {
	TetrisStatsHandler::TetrisStatsHandler(SDL_Renderer*& renderCtx, const Timer& timer, const SDL_Rect& tetrisViewPort, const TetrisStats& tetrisStats)
		: renderCtx(renderCtx), timer(timer), tetrisViewPort(tetrisViewPort), tetrisStats(tetrisStats)
	{
		this->MainFont = TTF_OpenFont("fonts/Silkscreen-Regular.ttf", 28);
		if (this->MainFont == NULL) {
			std::cout << "error: " << TTF_GetError() << '\n';
		}
	}

	void TetrisStatsHandler::Render() {
		std::cout << "lines cleared: " << tetrisStats.LinesCleared << " | " << "pieces locked: " << tetrisStats.PiecesLocked << '\n';


		// TEXT SECTION
		// render the texts

		// username text
		// calculate ratio of text to container width to make sure text fits its container (holdPieceArea)
		int tw, th;
		TTF_SizeText(this->MainFont, "Kenneth", &tw, &th);
		float twRatio = tetrisViewPort.w / 4 / tw;
		float thRatio = (float)th / tw;
		float newTw = twRatio * tw;
		float newTh = thRatio * twRatio * tw;
		SDL_FRect textRect{ 0, (float)tetrisViewPort.h / 3, newTw, newTh };

		SDL_Surface* textSurface = TTF_RenderText_Solid(this->MainFont, "Kenneth", { 255,255,255,255 });

		//Create texture from surface pixels
		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(this->renderCtx, textSurface);

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
		SDL_RenderCopyF(this->renderCtx, textTexture, NULL, &textRect);

		// delete the text texture
		SDL_DestroyTexture(textTexture);


		// time
		int currTimeInMS = this->timer.CurrentTick();

		using namespace std::chrono;
		auto d = (milliseconds)currTimeInMS;
		auto m = duration_cast<minutes>(d);
		d -= m;
		auto s = duration_cast<seconds>(d);

		std::stringstream ss;
		ss << m.count() << ":" << s.count();

		std::string msToMMSS = ss.str();


		TTF_SizeText(this->MainFont, msToMMSS.c_str(), &tw, &th);
		twRatio = tetrisViewPort.w / 4 / tw;
		thRatio = (float)th / tw;
		newTw = twRatio * tw;
		newTh = thRatio * twRatio * tw;
		textRect = { 0, (float)tetrisViewPort.h / 2, newTw, newTh };

		textSurface = TTF_RenderText_Solid(this->MainFont, msToMMSS.c_str(), { 255,255,255,255 });

		//Create texture from surface pixels
		textTexture = SDL_CreateTextureFromSurface(this->renderCtx, textSurface);

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
		SDL_RenderCopyF(this->renderCtx, textTexture, NULL, &textRect);

		// delete the text texture
		SDL_DestroyTexture(textTexture);

	}
}
#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H

#include "../GameStatesFileHandler.hpp"

#include <SDL.h>

#include <string>

namespace UI {
	class GameConfig {
	public:
		void Show();
		void Hide();
		bool IsShowing();
		void Render();
	private:
		void Save();

		bool isSettingKey = false;
		SDL_Scancode* keyToSet = nullptr;
		bool isShowing = false;
		bool hasError = false;
		std::string errorMsg = "";

		GameStatesFileHandler replacementSetting;
	};
}

#endif
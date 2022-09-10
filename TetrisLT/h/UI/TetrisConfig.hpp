#ifndef TETRIS_CONFIG_H
#define TETRIS_CONFIG_H

#include "../../h/TetrisSettingsFileHandler.hpp"

#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_sdl.h"
#include "../../imgui/imgui_impl_sdlrenderer.h"

#include <SDL.h>
#include <string>

namespace UI {

	class TetrisConfig {
	public:
		void Show();
		void Hide();
		bool IsShowing();
		void Render();
	private:
		void Save();
		void New();
		void Delete();
		void Rename();

		bool isSettingKey = false;
		SDL_Scancode* keyToSet = nullptr;
		bool isShowing = false;
		bool hasError = false;
		std::string errorMsg = "";
		int comboBoxIndexSelected = 0;
		char newSettingsBuffer[100] = "";
		char renameSettingNameBuffer[100] = "";
		char playerNameBuffer[100] = "";
		std::string previewComboBox;


		TetrisSettingsFileHandler replacementSetting;
	};
}

#endif
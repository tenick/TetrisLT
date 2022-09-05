#ifndef TETRIS_CONFIG_H
#define TETRIS_CONFIG_H

#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_sdl.h"
#include "../../imgui/imgui_impl_sdlrenderer.h"


namespace UI {

	class TetrisConfig {
	public:
		TetrisConfig(bool& show);
		void Show();
	private:
		bool& showTetrisConfig;
		char name[100] = "";
		char profileName[100] = "";
		int das = 5;
		int arr = 5;
		int sds = 5;
		int gravity = 5;
		int delayAfterLocking = 100;
		int lockDelay = 100;
		int lockDelayLimit = 15;
		bool enableGhostPiece;
		int boardWidth = 10;
		int boardHeight = 20;
		int vanishingZoneHeight = 20;
	};
}

#endif
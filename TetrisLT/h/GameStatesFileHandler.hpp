#ifndef GAME_STATES_FILE_HANDLER_H
#define GAME_STATES_FILE_HANDLER_H

#include <SDL.h>

#include <string>

struct GameStatesFileHandler {
	// general
	std::string SelectedTetrisSettingName;
	int SFXVolume = 80;

	// single player general stuff
	SDL_Scancode QuitKey = SDL_SCANCODE_ESCAPE;
	SDL_Scancode ResetKey = SDL_SCANCODE_R;

	// single player sprint specifics
	int StartCountdownTicks = 3;
	int StartCountdownTickDurationMS = 1000;
	int ResetCountdownTicks = 3;
	int ResetCountdownTickDurationMS = 400;
	int GameFinishDelayMS = 3000;

	bool LoadFromFile();
	void WriteToFile();
	bool IsKeyUsed(SDL_Scancode key);
};

#endif